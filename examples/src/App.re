open ReactDND;

type action =
  | Add(string);

type state = {data: array(Records.item)};

let component = ReasonReact.reducerComponent("App");

let draggable: array(Records.item) = [|
  {name: "apple"},
  {name: "banana"},
  {name: "orange"},
|];

let make = _children => {
  ...component,
  initialState: () => {data: [||]},
  reducer: (action, state) =>
    switch (action) {
    | Add(name) =>
      ReasonReact.Update({
        data: Array.concat([state.data, [|{name: name}|]]),
      })
    },
  render: self =>
    <DragDropContextProvider backend=DnDBackend.html5>
      <div className="App">
        <div className="App-main"> <Basket data=self.state.data /> </div>
        <div className="App-sidebar">
          (
            ReasonReact.arrayToElement(
              Array.map(
                (item: Records.item) =>
                  <Item
                    key=item.name
                    name=item.name
                    onEndDrag=(() => self.send(Add(item.name)))
                  />,
                draggable,
              ),
            )
          )
        </div>
      </div>
    </DragDropContextProvider>,
};