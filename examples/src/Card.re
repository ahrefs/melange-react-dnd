open Belt;

module Dnd = {
  let itemTypeId = "card";

  type dragItem = {
    .
    "id": int,
    "startIndex": int,
  };

  type dropItem = Js.Dict.t(unit);
};

module DropTargetSpec =
  BsReactDnd.DropTarget.MakeSpec({
    type dragItem = Dnd.dragItem;
    type dropItem = Dnd.dropItem;
    type props = {
      .
      "id": int,
      "moveCard": [@bs.meth] ((int, int) => unit),
      "dropCard": [@bs.meth] ((int, int) => unit),
    };
  });

module DropTargetWrapper =
  BsReactDnd.DropTarget.Make({
    let itemType = Dnd.itemTypeId;
    type spec = DropTargetSpec.t;
    let spec: spec =
      DropTargetSpec.make(
        ~hover=
          (props, monitor, _component) => {
            let dragItem = monitor##getItem() |> Js.toOption;
            let hoverId = props##id;
            switch (dragItem) {
            | Some(dragItem) when dragItem##id !== hoverId =>
              /* Time to actually perform the action */
              props##moveCard(dragItem##id, hoverId)
            | Some(_)
            | None => ()
            };
          },
        ~drop=
          (props, monitor, _component) => {
            let dragItem = monitor##getItem() |> Js.toOption;
            dragItem
            ->Option.map(dragItem =>
                props##dropCard(dragItem##id, dragItem##startIndex)
              )
            ->ignore;
            Js.Dict.empty();
          },
        (),
      );
    type collectedProps = {. "connectDropTarget": BsReactDnd.Utils.wrapper};
    type collect =
      (BsReactDnd.DropTarget.connector, DropTargetSpec.monitor) =>
      collectedProps;
    let collect: collect =
      (connect, _) => {"connectDropTarget": connect##dropTarget()};
  });

module DragSourceSpec =
  BsReactDnd.DragSource.MakeSpec({
    type dragItem = Dnd.dragItem;
    type dropItem = Dnd.dropItem;
    type props = Dnd.dragItem;
  });

module DragSourceWrapper =
  BsReactDnd.DragSource.Make({
    let itemType = Dnd.itemTypeId;
    type spec = DragSourceSpec.t;
    let spec: spec =
      DragSourceSpec.make(
        ~beginDrag=
          (props, _, _) =>
            {"id": props##id, "startIndex": props##startIndex},
        (),
      );
    type collectedProps = {
      .
      "connectDragSource": BsReactDnd.Utils.wrapper,
      "connectDragPreview": BsReactDnd.DragSource.dragPreview,
      "isDragging": bool,
    };
    type collect =
      (BsReactDnd.DragSource.connector, DragSourceSpec.monitor) =>
      collectedProps;
    let collect: collect =
      (connect, monitor) => {
        "connectDragSource": connect##dragSource(),
        "connectDragPreview": connect##dragPreview(),
        "isDragging": monitor##isDragging(),
      };
  });

let component = ReasonReact.statelessComponent("Card");

let make = (~id, ~text, ~index, ~moveCard, ~dropCard, _children) => {
  ...component,
  render: _self =>
    /* need to be very carefull when passing `props` isn't annotated, this has to be the same as DragSourceSpec.props */
    <DropTargetWrapper
      props={"id": id, "moveCard": moveCard, "dropCard": dropCard}>
      ...{(~collectedProps as dropTarget) =>
        <DragSourceWrapper props={"id": id, "startIndex": index}>
          ...{(~collectedProps as dragSource) =>
            dropTarget##connectDropTarget(
              dragSource##connectDragPreview(
                <div
                  style={ReactDOMRe.Style.make(
                    ~display="flex",
                    ~border=
                      Printf.sprintf(
                        "1px %s gray",
                        dragSource##isDragging ? "dashed" : "solid",
                      ),
                    ~padding="0.5rem 1rem",
                    ~marginBottom=".5rem",
                    ~backgroundColor="white",
                    ~opacity=dragSource##isDragging ? "0" : "1",
                    (),
                  )}>
                  {dragSource##connectDragSource(
                     <div
                       style={ReactDOMRe.Style.make(
                         ~cursor=dragSource##isDragging ? "grabbing" : "grab",
                         ~borderRadius="5px",
                         ~width="14px",
                         ~height="14px",
                         ~marginRight="0.5rem",
                         ~backgroundColor="lightsalmon",
                         (),
                       )}
                     />,
                   )}
                  {ReasonReact.string(text)}
                </div>,
                BsReactDnd.DragSource.makeDragPreviewOptions(),
              ),
            )
          }
        </DragSourceWrapper>
      }
    </DropTargetWrapper>,
};
