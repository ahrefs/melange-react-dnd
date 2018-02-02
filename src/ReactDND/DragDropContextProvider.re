type dndBackend;

[@bs.module] external html5backend : dndBackend = "react-dnd-html5-backend";

[@bs.module "react-dnd"]
external reactClass : ReasonReact.reactClass = "DragDropContextProvider";

let make = (~backend: dndBackend, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={"backend": backend},
    children
  );