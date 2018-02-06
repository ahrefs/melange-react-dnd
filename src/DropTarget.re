/* DropTarget
 * https://react-dnd.github.io/react-dnd/docs-drop-target.html
 */
open Core;

type monitor = {
  .
  "getItem": [@bs.meth] (unit => option(dndItem)),
  "isOver": [@bs.meth] (unit => Js.boolean),
  "canDrop": [@bs.meth] (unit => Js.boolean)
};

module MakeSpec = (Config: {type props;}) => {
  type t = {
    .
    "drop": (Config.props, monitor) => dndItem,
    "hover": (Config.props, monitor) => unit,
    "canDrop": (Config.props, monitor) => bool
  };
  [@bs.obj]
  external make :
    (
      ~drop: (Config.props, monitor) => dndItem=?,
      ~hover: (Config.props, monitor) => unit=?,
      ~canDrop: (Config.props, monitor) => bool=?,
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
  external dropTarget : (string, Config.spec, Config.collect) => hoc =
    "DropTarget";
  type children =
    (~collectedProps: Config.collectedProps) => ReasonReact.reactElement;
  let component = ReasonReact.statelessComponent("DropTarget");
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
    dropTarget(Config.itemType, Config.spec, Config.collect, jsComponent);
  /* Convert JS => Reason */
  let make = (~props=Js.Obj.empty(), children: children) =>
    ReasonReact.wrapJsForReason(~reactClass=enhanced, ~props, children);
};