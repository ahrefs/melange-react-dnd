/* DragSource
 * https://react-dnd.github.io/react-dnd/docs-drag-source.html
 */
open Core;

type monitor = {
  .
  "getItem": [@bs.meth] (unit => dndItem),
  "getDropResult": [@bs.meth] (unit => dndItem)
};

module MakeSpec = (Config: {type props;}) => {
  type t = {
    .
    "beginDrag": Config.props => dndItem,
    "endDrag": (Config.props, monitor) => unit
  };
  [@bs.obj]
  external make :
    (
      ~beginDrag: Config.props => dndItem=?,
      ~endDrag: (Config.props, monitor) => unit=?,
      unit
    ) =>
    t =
    "";
};

module type MakeConfig = {
  type spec;
  type collectedProps;
  type collect;
  let itemType: string;
  let spec: spec;
  let collect: collect;
};

module Make = (Config: MakeConfig) => {
  external convertToCollectedProps : Js.t({..}) => Config.collectedProps =
    "%identity";
  [@bs.module "react-dnd"]
  external dragSource : (string, Config.spec, Config.collect) => hoc =
    "DragSource";
  type children =
    (~collectedProps: Config.collectedProps) => ReasonReact.reactElement;
  let component = ReasonReact.statelessComponent("DragSource");
  let make' = (~collectedProps: Config.collectedProps, children: children) => {
    ...component,
    render: _self => children(~collectedProps)
  };
  /* Convert Reason => JS */
  let jsComponent =
    ReasonReact.wrapReasonForJs(~component, (props: {. "children": children}) =>
      make'(~collectedProps=convertToCollectedProps(props), props##children)
    );
  /* Wrap JS class with 'react-dnd' */
  let enhanced =
    dragSource(Config.itemType, Config.spec, Config.collect, jsComponent);
  /* Convert JS => Reason */
  let make = (~props=Js.Obj.empty(), children: children) =>
    ReasonReact.wrapJsForReason(~reactClass=enhanced, ~props, children);
};