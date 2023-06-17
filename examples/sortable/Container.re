open Belt;

module RList = {
  // From https://github.com/jonlaing/rationale/blob/06a48fd39b106319a4a4477e90777db51c915353/src/RList.re
  let append = (a, xs) => Stdlib.List.append(xs, [a]);
  let concat = (xs, ys) => Stdlib.List.append(ys, xs);
  let take = {
    let rec loop = (i, xs, acc) =>
      switch (i, xs) {
      | (i, _) when i <= 0 => acc
      | (_, []) => acc
      | (i, [a, ...b]) => loop(i - 1, b, append(a, acc))
      };
    (i, xs) => loop(i, xs, []);
  };

  let takeLast = (i, xs) =>
    Stdlib.List.rev(xs) |> take(i) |> Stdlib.List.rev;
  let splitAt = (i, xs) => (
    take(i, xs),
    takeLast(List.length(xs) - i, xs),
  );
  let insert = (i, x, xs) => {
    let (a, b) = splitAt(i, xs);
    a |> append(x) |> concat(b);
  };
  let rec drop = (i, xs) =>
    switch (i, xs) {
    | (_, []) => []
    | (i, _) when i <= 0 => xs
    | (i, [_, ...b]) => drop(i - 1, b)
    };
  let remove = (i, n, xs) => {
    let (a, b) = splitAt(i, xs);
    a @ drop(n, b);
  };
};

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

  <ReactDnd.DndProvider backend=ReactDnd.Backend.html5>
    <div style={ReactDOM.Style.make(~width="400", ())}>
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
       ->React.array}
    </div>
  </ReactDnd.DndProvider>;
};
