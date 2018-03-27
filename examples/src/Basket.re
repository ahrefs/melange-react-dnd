module DropTargetSpec =
  ReactDND.DropTarget.MakeSpec(
    {
      type dragItem = Const.dragItem;
      type dropItem = Const.dropItem;
      type props = unit;
    },
  );

module DropTargetWrapper =
  ReactDND.DropTarget.Make(
    {
      let itemType = Const.itemType;
      type spec = DropTargetSpec.t;
      let spec: spec = DropTargetSpec.make();
      type collectedProps = {
        .
        "connectDropTarget": ReactDND.Core.wrapper,
        "isOver": bool,
        "canDrop": bool,
      };
      type collect =
        (ReactDND.DropTarget.connector, DropTargetSpec.monitor) =>
        collectedProps;
      let collect: collect =
        (connect, monitor) => {
          "connectDropTarget": connect##dropTarget(),
          "isOver": Js.to_bool(monitor##isOver({"shallow": Js.false_})),
          "canDrop": Js.to_bool(monitor##canDrop()),
        };
    },
  );

let component = ReasonReact.statelessComponent("Basket");

let make = (~data: array(Records.item), _children) => {
  ...component,
  render: _self =>
    <DropTargetWrapper>
      ...(
           (~collectedProps) =>
             collectedProps##connectDropTarget(
               <div
                 className="Basket"
                 style=(
                   ReactDOMRe.Style.make(
                     ~backgroundColor=
                       collectedProps##isOver && collectedProps##canDrop ?
                         "lightgreen" : "white",
                     (),
                   )
                 )>
                 <p>
                   (ReasonReact.stringToElement("items in the basket:"))
                 </p>
                 <ul>
                   (
                     ReasonReact.arrayToElement(
                       Array.map(
                         (item: Records.item) =>
                           <li key=item.name>
                             (ReasonReact.stringToElement(item.name))
                           </li>,
                         data,
                       ),
                     )
                   )
                 </ul>
               </div>,
             )
         )
    </DropTargetWrapper>,
};