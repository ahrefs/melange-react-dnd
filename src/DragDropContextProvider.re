[@bs.module "react-dnd"]
external reactClass : ReasonReact.reactClass = "DragDropContextProvider";

let make = (~backend: Backend.t, ~window=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props={"backend": backend, "window": Js.Nullable.fromOption(window)},
    children,
  );