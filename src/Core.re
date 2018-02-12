type hoc = ReasonReact.reactClass => ReasonReact.reactClass;

type wrapper =
  [@bs.meth] (ReasonReact.reactElement => ReasonReact.reactElement);

type connect = {
  .
  "dragSource": [@bs.meth] (unit => wrapper),
  "dragPreview": [@bs.meth] (unit => wrapper),
  "dropTarget": [@bs.meth] (unit => wrapper)
};

type coordinates = {
  .
  "x": int,
  "y": int
};