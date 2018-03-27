module DragSourceSpec =
  ReactDND.DragSource.MakeSpec(
    {
      type dndItem = {. "name": string};
      type props = {. "onEndDrag": [@bs.meth] (unit => unit)};
    },
  );

module DragSourceWrapper =
  ReactDND.DragSource.Make(
    {
      let itemType: string = "BOX";
      type spec = DragSourceSpec.t;
      let spec: spec =
        DragSourceSpec.make(
          ~beginDrag=(_, _, _) => {"name": "Item"},
          ~endDrag=
            (props, monitor, _) => {
              /* let item = monitor##getItem(); */
              let dropResult = Js.toOption(monitor##getDropResult());
              switch (dropResult) {
              | Some(_) => props##onEndDrag()
              | None => ()
              };
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