open Belt;

type action =
  | MoveCard(int, int)
  | DropCard(int);

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

      switch (dragIndex, hoverIndex) {
      | ((-1), _)
      | (_, (-1)) => ReasonReact.NoUpdate
      | (dragIndex, hoverIndex) =>
        let dragCard = cards->Array.getExn(dragIndex);
        let hoverCard = cards->Array.getExn(hoverIndex);
        ReasonReact.Update({
          cards:
            state.cards
            ->Array.mapWithIndex((i, card) =>
                switch (i) {
                | i when i == dragIndex => hoverCard
                | i when i == hoverIndex => dragCard
                | _ => card
                }
              ),
        });
      };
    | DropCard(id) =>
      ReasonReact.SideEffects(
        _ =>
          state.cards
          ->Js.Array.find(card => card.T.id == id, _)
          ->Option.map(card => Js.log2("DropCard", card))
          ->ignore,
      )
    },
  render: ({state, send}) => {
    <BsReactDnd.DragDropContextProvider backend=BsReactDnd.Backend.html5>
      <div style={ReactDOMRe.Style.make(~width="400", ())}>
        {state.cards
         ->Array.map(card =>
             <Card
               key={string_of_int(card.id)}
               id={card.id}
               text={card.text}
               moveCard={(dragIndex, hoverIndex) =>
                 send(MoveCard(dragIndex, hoverIndex))
               }
               dropCard={id => send(DropCard(id))}
             />
           )
         ->ReasonReact.array}
      </div>
    </BsReactDnd.DragDropContextProvider>;
  },
};
