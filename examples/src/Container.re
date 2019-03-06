open Belt;

// Return copy of given array, switching the elements at the given positions
let switchElements = (array, i, j) =>
  i == j ?
    array :
    (
      switch (array->Array.get(i), array->Array.get(j)) {
      | (Some(ei), Some(ej)) =>
        array->Array.mapWithIndex((index, v) =>
          switch (index) {
          | index when index == i => ej
          | index when index == j => ei
          | _ => v
          }
        )
      | _ => array
      }
    );

type action =
  | MoveCard(int, int)
  | DropCard(int, int);

type state = {cards: array(T.card)};

let component = ReasonReact.reducerComponent(__MODULE__);

let make = _children => {
  ...component,
  initialState: () => {
    cards: [|
      {id: 1, text: "Write a cool JS library"},
      {id: 2, text: "Make it generic enough"},
      {id: 3, text: "Write README"},
      {id: 4, text: "Create some examples"},
      {id: 5, text: "Spam in Twitter and IRC to promote it"},
      {id: 6, text: "???"},
      {id: 7, text: "PROFIT"},
    |],
  },
  reducer: (action, state) =>
    switch (action) {
    | MoveCard(dragId, hoverId) =>
      let cards = state.cards;
      let dragIndex = cards |> Js.Array.findIndex(card => card.T.id == dragId);
      let hoverIndex =
        cards |> Js.Array.findIndex(card => card.T.id == hoverId);

      Js.log3("MoveCard:", dragIndex, hoverIndex);

      ReasonReact.Update({
        cards: state.cards->switchElements(dragIndex, hoverIndex),
      });
    | DropCard(id, startIndex) =>
      ReasonReact.SideEffects(
        _ => {
          let currentIndex =
            state.cards |> Js.Array.findIndex(card => card.T.id == id);
          if (startIndex == currentIndex) {
            Js.log("Card was dropped into old position!");
          } else {
            state.cards
            ->Array.get(currentIndex)
            ->Option.map(card =>
                Js.log2("Card was dropped into new position:", card)
              )
            ->ignore;
          };
        },
      )
    },
  render: ({state, send}) => {
    <BsReactDnd.DragDropContextProvider backend=BsReactDnd.Backend.html5>
      <div style={ReactDOMRe.Style.make(~width="400", ())}>
        {state.cards
         ->Array.mapWithIndex((index, card) =>
             <Card
               key={string_of_int(card.id)}
               id={card.id}
               text={card.text}
               index
               moveCard={(dragIndex, hoverIndex) =>
                 send(MoveCard(dragIndex, hoverIndex))
               }
               dropCard={(id, startIndex) => send(DropCard(id, startIndex))}
             />
           )
         ->ReasonReact.array}
      </div>
    </BsReactDnd.DragDropContextProvider>;
  },
};
