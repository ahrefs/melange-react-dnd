/* DropTarget
 * https://react-dnd.github.io/react-dnd/docs-drop-target.html
 */
open Core;

type connector = {. "dropTarget": [@bs.meth] (unit => wrapper)};

module MakeSpec = (Config: {type props; type dragItem; type dropItem;}) => {
  type monitor = {
    .
    "canDrop": [@bs.meth] (unit => Js.boolean),
    "isOver": [@bs.meth] ({. "shallow": Js.boolean} => Js.boolean),
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
    "drop": (Config.props, monitor, ReasonReact.reactRef) => Config.dropItem,
    "hover": (Config.props, monitor, ReasonReact.reactRef) => unit,
    "canDrop": (Config.props, monitor) => bool,
  };
  [@bs.obj]
  external make :
    (
      ~drop: (Config.props, monitor, ReasonReact.reactRef) => Config.dropItem=?,
      ~hover: (Config.props, monitor, ReasonReact.reactRef) => unit=?,
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
  let itemType: itemType;
  let spec: spec;
  let collect: collect;
};

module Make = (Config: MakeConfig) => {
  external convertToCollectedProps : Js.t({..}) => Config.collectedProps =
    "%identity";
  [@bs.module "react-dnd"]
  external dropTarget : (itemType, Config.spec, Config.collect) => hoc =
    "DropTarget";
  type children =
    (~collectedProps: Config.collectedProps) => ReasonReact.reactElement;
  let component = ReasonReact.statelessComponent("DropTarget");
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
    dropTarget(Config.itemType, Config.spec, Config.collect, jsComponent);
  /* Convert JS => Reason */
  let make = (~props=Js.Obj.empty(), children: children) =>
    ReasonReact.wrapJsForReason(~reactClass=enhanced, ~props, children);
};