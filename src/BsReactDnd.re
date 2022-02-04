module Backend = {
  type t;
  [@bs.module "react-dnd-html5-backend"] external html5: t = "HTML5Backend";
};

module DndProvider = {
  [@bs.module "react-dnd"] [@react.component]
  external make:
    (~backend: Backend.t, ~children: React.element=?) => React.element =
    "DndProvider";
};

type useDragItemProps('id) = {
  id: 'id,
  index: ref(int),
};

type useDragCollectedProps = {isDragging: bool};

type dragMonitor = {. [@bs.meth] "isDragging": unit => bool};

type useDragProps('id) = {
  [@bs.as "type"]
  type_: string,
  item: useDragItemProps('id),
  collect: dragMonitor => useDragCollectedProps,
  canDrag: dragMonitor => bool,
};

[@bs.module "react-dnd"]
external useDrag:
  useDragProps('id) =>
  (useDragCollectedProps, ReactDOM.domRef => ReactDOM.domRef) =
  "useDrag";

type clientOffset = {
  x: int,
  y: int,
};

type dropMonitor = {
  .
  [@bs.meth] "getClientOffset": unit => clientOffset,
  [@bs.meth] "canDrop": unit => bool,
};

type useDropProps('id) = {
  accept: string,
  hover: (useDragItemProps('id), dropMonitor) => unit,
  canDrop: dropMonitor => bool,
};

[@bs.module "react-dnd"]
external useDrop:
  useDropProps('id) => ('b, ReactDOM.domRef => ReactDOM.domRef) =
  "useDrop";
