[@react.component]
let make = (~id, ~text, ~fixed, ~index, ~moveCard) => {
  let elementRef = React.useRef(Js.Nullable.null);

  let (_, drop) =
    ReactDnd.useDrop({
      accept: T.itemType,
      canDrop: _ => !fixed,
      hover: (item, monitor) => {
        elementRef.current
        ->Js.toOption
        ->Belt.Option.forEach(el => {
            let dragIndex = item.index^;
            let hoverIndex = index;

            if (dragIndex != hoverIndex) {
              let hoverBoundingRect =
                el->Webapi.Dom.Element.getBoundingClientRect;

              let hoverBoundingRectBottom =
                hoverBoundingRect->Webapi.Dom.DomRect.bottom;

              let hoverBoundingRectTop =
                hoverBoundingRect->Webapi.Dom.DomRect.top;

              let hoverMiddleY =
                (hoverBoundingRectBottom -. hoverBoundingRectTop) /. 2.;

              let clientOffset = monitor##getClientOffset();

              let hoverClientY =
                clientOffset.y->Belt.Int.toFloat -. hoverBoundingRectTop;

              if (dragIndex < hoverIndex && hoverClientY < hoverMiddleY) {
                ();
              } else if (dragIndex > hoverIndex && hoverClientY > hoverMiddleY) {
                ();
              } else if (monitor##canDrop()) {
                moveCard(dragIndex, hoverIndex);

                item.index := hoverIndex;
              };
            };
          });
      },
    });

  let (collectedProps, drag) =
    ReactDnd.useDrag({
      type_: T.itemType,
      item: {
        id,
        index: ref(index),
      },
      canDrag: _ => !fixed,
      collect: monitor => {
        {isDragging: monitor##isDragging()};
      },
    });

  <div
    ref={elementRef->ReactDOM.Ref.domRef->drop->drag}
    style={ReactDOM.Style.make(
      ~border="1px dashed gray",
      ~padding="0.5rem 1rem",
      ~marginBottom=".5rem",
      ~color=fixed ? "#999" : "#333",
      ~backgroundColor=fixed ? "#eee" : "white",
      ~cursor=fixed ? "default" : "move",
      ~opacity=collectedProps.isDragging ? "0" : "1",
      (),
    )}>
    {React.string(text)}
  </div>;
};
