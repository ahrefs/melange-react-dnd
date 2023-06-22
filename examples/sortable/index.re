let component =
  <>
    <p>
      <b>
        <a
          href="https://github.com/ahrefs/melange-react-dnd/tree/master/examples/sortable">
          {React.string("ReasonML source code")}
        </a>
        <br />
        <a
          href="https://github.com/react-dnd/react-dnd/tree/master/packages/documentation/examples/04%20Sortable/Simple">
          {React.string("Original JavaScript example")}
        </a>
      </b>
    </p>
    <p>
      {React.string(
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
