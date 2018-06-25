/* DragSource
 * https://react-dnd.github.io/react-dnd/docs-drag-source.html
 */
open BsReactDnd__Utils;

type dragPreviewOptions = {
  .
  "captureDraggingState": Js.undefined(bool),
  "anchorX": Js.undefined(float),
  "anchorY": Js.undefined(float),
  "offsetX": Js.undefined(int),
  "offsetY": Js.undefined(int),
};

let makeDragPreviewOptions =
    (
      ~captureDraggingState=?,
      ~anchorX=?,
      ~anchorY=?,
      ~offsetX=?,
      ~offsetY=?,
      (),
    )
    : dragPreviewOptions => {
  "captureDraggingState": captureDraggingState |. Js.Undefined.fromOption,
  "anchorX": anchorX |. Js.Undefined.fromOption,
  "anchorY": anchorY |. Js.Undefined.fromOption,
  "offsetX": offsetX |. Js.Undefined.fromOption,
  "offsetY": offsetY |. Js.Undefined.fromOption,
};

type dragPreview =
  [@bs.meth] (
    (ReasonReact.reactElement, dragPreviewOptions) => ReasonReact.reactElement
  );

type connector = {
  .
  "dragSource": [@bs.meth] (unit => wrapper),
  "dragPreview": [@bs.meth] (unit => dragPreview),
};

module MakeSpec = (Config: {type props; type dragItem; type dropItem;}) => {
  type monitor = {
    .
    "canDrag": [@bs.meth] (unit => bool),
    "isDragging": [@bs.meth] (unit => bool),
    "getItemType": [@bs.meth] (unit => Js.nullable(itemType)),
    "getItem": [@bs.meth] (unit => Js.nullable(Config.dragItem)),
    "getDropResult": [@bs.meth] (unit => Js.nullable(Config.dropItem)),
    "didDrop": [@bs.meth] (unit => bool),
    "getInitialClientOffset": [@bs.meth] (unit => Js.nullable(coordinates)),
    "getInitialSourceClientOffset":
      [@bs.meth] (unit => Js.nullable(coordinates)),
    "getClientOffset": [@bs.meth] (unit => Js.nullable(coordinates)),
    "getDifferenceFromInitialOffset":
      [@bs.meth] (unit => Js.nullable(coordinates)),
    "getSourceClientOffset": [@bs.meth] (unit => Js.nullable(coordinates)),
  };
  type t;
  [@bs.obj]
  external make :
    (
      ~beginDrag: (Config.props, monitor, ReasonReact.reactRef) =>
                  Config.dragItem,
      ~endDrag: (Config.props, monitor, ReasonReact.reactRef) => unit=?,
      ~canDrag: (Config.props, monitor) => bool=?,
      ~isDragging: (Config.props, monitor) => bool=?,
      unit
    ) =>
    t =
    "";
};

module Make =
       (
         Config: {
           type spec;
           type collectedProps;
           type collect;
           let itemType: itemType;
           let spec: spec;
           let collect: collect;
         },
       ) => {
  external convertToCollectedProps : Js.t({..}) => Config.collectedProps =
    "%identity";
  [@bs.module "react-dnd"]
  external dragSource : (itemType, Config.spec, Config.collect) => hoc =
    "DragSource";
  type children =
    (~collectedProps: Config.collectedProps) => ReasonReact.reactElement;
  let component = ReasonReact.statelessComponent("DragSource");
  let make' = (~collectedProps: Config.collectedProps, children: children) => {
    ...component,
    render: _self => children(~collectedProps),
  };
  /* Convert Reason => JS */
  let jsComponent =
    ReasonReact.wrapReasonForJs(
      ~component, (props: {. "children": children}) =>
      make'(~collectedProps=convertToCollectedProps(props), props##children)
    );
  /* Wrap JS class with 'react-dnd' */
  let enhanced =
    dragSource(Config.itemType, Config.spec, Config.collect, jsComponent);

  /* Convert JS => Reason */
  let make = (~props=Js.Obj.empty(), children: children) =>
    ReasonReact.wrapJsForReason(~reactClass=enhanced, ~props, children);
};
