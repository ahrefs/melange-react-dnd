let component =
  <>
    <p>
      <b>
        <a
          href="https://github.com/ahrefs/bs-react-dnd/tree/master/examples/sortable">
          {ReasonReact.string("ReasonML source code")}
        </a>
        <br />
        <a
          href="https://github.com/react-dnd/react-dnd/tree/master/packages/documentation/examples/04%20Sortable/Simple">
          {ReasonReact.string("Original JavaScript example")}
        </a>
      </b>
    </p>
    <p>
      {ReasonReact.string(
         "It is easy to implement a sortable interface with React DnD. Just make the same component both a drag source and a drop target, and reorder the data in the 'hover' handler.",
       )}
    </p>
    <Container />
  </>;

let id = "root";

switch (ReactDOM.querySelector("#" ++ id)) {
| Some(node) => ReactDOM.render(component, node)
| None =>
  Js.Console.error(
    "RR.renderToElementWithId : no element of id "
    ++ id
    ++ " found in the HTML.",
  )
};
