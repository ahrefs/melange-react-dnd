type hoc = ReasonReact.reactClass => ReasonReact.reactClass;

type wrapper =
  [@bs.meth] (ReasonReact.reactElement => ReasonReact.reactElement);

/* The React DnD docs say that this can also be the ES6 Symbol. */
type identifier = string;

type coordinates = {
  .
  "x": int,
  "y": int,
};