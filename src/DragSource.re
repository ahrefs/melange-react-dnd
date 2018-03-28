/* DragSource
 * https://react-dnd.github.io/react-dnd/docs-drag-source.html
 */
open Core;

type connector = {
  .
  "dragSource": [@bs.meth] (unit => wrapper),
  "dragPreview": [@bs.meth] (unit => wrapper),
};

module MakeSpec = (Config: {type props; type dragItem; type dropItem;}) => {
  type monitor = {
    .
    "canDrag": [@bs.meth] (unit => Js.boolean),
    "isDragging": [@bs.meth] (unit => Js.boolean),
    "getItemType": [@bs.meth] (unit => Js.nullable(Core.itemType)),
    "getItem": [@bs.meth] (unit => Js.nullable(Config.dragItem)),
    "getDropResult": [@bs.meth] (unit => Js.nullable(Config.dropItem)),
    "didDrop": [@bs.meth] (unit => Js.boolean),
    "getInitialClientOffset": [@bs.meth] (unit => Js.nullable(coordinates)),
    "getInitialSourceClientOffset":
      [@bs.meth] (unit => Js.nullable(coordinates)),
    "getClientOffset": [@bs.meth] (unit => Js.nullable(coordinates)),
    "getDifferenceFromInitialOffset":
      [@bs.meth] (unit => Js.nullable(coordinates)),
    "getSourceClientOffset": [@bs.meth] (unit => Js.nullable(coordinates)),
  };
  type t = {
    .
    "beginDrag":
      (Config.props, monitor, ReasonReact.reactRef) => Config.dragItem,
    "endDrag": (Config.props, monitor, ReasonReact.reactRef) => unit,
    "canDrag": (Config.props, monitor) => bool,
    "isDragging": (Config.props, monitor) => bool,
  };
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