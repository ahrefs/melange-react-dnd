module DragSourceSpec =
  ReactDND.DragSource.MakeSpec(
    {
      type dragItem = unit;
      type dropItem = unit;
      type props = {. "onEndDrag": [@bs.meth] (unit => unit)};
    },
  );

module DragSourceWrapper =
  ReactDND.DragSource.Make(
    {
      let itemType: ReactDND.Core.identifier = "BOX";
      type spec = DragSourceSpec.t;
      let spec: spec =
        DragSourceSpec.make(
          ~beginDrag=(_, _, _) => (),
          ~endDrag=
            (props, monitor, _) => {
              Js.to_bool(monitor##didDrop()) ? props##onEndDrag() : ();
              ();
            },
          (),
        );
      type collectedProps = {. "connectDragSource": ReactDND.Core.wrapper};
      type collect =
        (ReactDND.DragSource.connector, DragSourceSpec.monitor) =>
        collectedProps;
      let collect: collect =
        (connect, _monitor) => {"connectDragSource": connect##dragSource()};
    },
  );

let component = ReasonReact.statelessComponent("Item");

let make = (~name: string, ~onEndDrag: unit => unit, _children) => {
  ...component,
  render: _self =>
    <DragSourceWrapper props={"onEndDrag": onEndDrag}>
      ...(
           (~collectedProps) =>
             collectedProps##connectDragSource(
               <div className="Item">
                 (ReasonReact.stringToElement(name))
               </div>,
             )
         )
    </DragSourceWrapper>,
};