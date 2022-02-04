open Belt;

module RList = Rationale.RList;

let initialCards: list(T.card) = [
  {id: "1", text: "Write a cool JS library", fixed: true},
  {id: "2", text: "Make it generic enough", fixed: true},
  {id: "3", text: "Write README", fixed: false},
  {id: "4", text: "Create some examples", fixed: false},
  {id: "5", text: "Spam in Twitter and IRC to promote it", fixed: false},
  {id: "6", text: "???", fixed: false},
  {id: "7", text: "PROFIT", fixed: false},
];

[@react.component]
let make = () => {
  let (cards, setCards) = React.useState(_ => initialCards);

  let moveCard = (dragIndex, hoverIndex) => {
    let card = List.getExn(cards, dragIndex);

    setCards(_ =>
      cards->RList.remove(dragIndex, 1, _)->RList.insert(hoverIndex, card, _)
    );
  };

  <BsReactDnd.DndProvider backend=BsReactDnd.Backend.html5>
    <div style={ReactDOMRe.Style.make(~width="400", ())}>
      {cards
       ->List.mapWithIndex((index, card: T.card) =>
           <Card
             key={card.id}
             id={card.id}
             text={card.text}
             fixed={card.fixed}
             index
             moveCard
           />
         )
       ->List.toArray
       ->ReasonReact.array}
    </div>
  </BsReactDnd.DndProvider>;
};
