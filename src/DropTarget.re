/* DropTarget
 * https://react-dnd.github.io/react-dnd/docs-drop-target.html
 */
open Core;

type monitor = {
  .
  "isOver": [@bs.meth] (unit => Js.boolean),
  "canDrop": [@bs.meth] (unit => Js.boolean)
};

module MakeSpec = (Config: {type props;}) => {
  type t = {. "drop": unit => dndItem};
  [@bs.obj] external make : (~drop: Config.props => dndItem=?, unit) => t = "";
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
  let make = (children: children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=enhanced,
      ~props=Js.Obj.empty(),
      children
    );
};