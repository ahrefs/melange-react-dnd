ReactDOMRe.renderToElementWithId(
  <>
    <p>
      <b>
        <a
          href="https://github.com/ahrefs/bs-react-dnd/tree/master/examples/src">
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
      {
        ReasonReact.string(
          "It is easy to implement a sortable interface with React DnD. Just make the same component both a drag source and a drop target, and reorder the data in the 'hover' handler.",
        )
      }
    </p>
    <Container />
  </>,
  "root",
);
