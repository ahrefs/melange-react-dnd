let itemType = "card";

type dragItem = {. "id": int};

type dropItem = Js.Dict.t(unit);

type card = {
  id: string,
  text: string,
  fixed: bool,
};
