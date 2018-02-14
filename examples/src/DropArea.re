module DropTargetSpec =
  ReactDND.DropTarget.MakeSpec(
    {
      type dndItem = {. "name": string};
      type props = unit;
    }
  );

module DropTargetWrapper =
  ReactDND.DropTarget.Make(
    {
      type spec = DropTargetSpec.t;
      type collectedProps = {
        .
        "connectDropTarget": ReactDND.Core.wrapper,
        "isOver": bool,
        "canDrop": bool
      };
      type collect =
        (ReactDND.Core.connect, DropTargetSpec.monitor) => collectedProps;
      let itemType: string = "BOX";
      let spec: spec =
        DropTargetSpec.make(~drop=(_, _, _) => {"name": "DropArea"}, ());
      let collect: collect =
        (connect, monitor) => {
          "connectDropTarget": connect##dropTarget(),
          "isOver": Js.to_bool(monitor##isOver({"shallow": Js.false_})),
          "canDrop": Js.to_bool(monitor##canDrop())
        };
    }
  );

let component = ReasonReact.statelessComponent("DropArea");

let make = (~data: array(Records.item), _children) => {
  ...component,
  render: _self =>
    <DropTargetWrapper>
      ...(
           (~collectedProps) =>
             collectedProps##connectDropTarget(
               <div
                 className="DropArea"
                 style=(
                   ReactDOMRe.Style.make(
                     ~backgroundColor=
                       collectedProps##isOver && collectedProps##canDrop ?
                         "lightgreen" : "white",
                     ()
                   )
                 )>
                 <p> (ReasonReact.stringToElement("items in the basket:")) </p>
                 <ul>
                   (
                     ReasonReact.arrayToElement(
                       Array.map(
                         (item: Records.item) =>
                           <li key=item.name>
                             (ReasonReact.stringToElement(item.name))
                           </li>,
                         data
                       )
                     )
                   )
                 </ul>
               </div>
             )
         )
    </DropTargetWrapper>
};