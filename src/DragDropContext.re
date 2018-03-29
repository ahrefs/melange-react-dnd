[@bs.module "react-dnd"]
external reactClass : ReasonReact.reactClass = "DragDropContext";

let make = (~backend: Backend.t, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={"backend": backend},
    children,
  );