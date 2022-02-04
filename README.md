# Reason bindings for react-dnd

[Reason](https://reasonml.github.io/) bindings for [react-dnd](https://github.com/react-dnd/react-dnd).

## Status

🚧 Not everything is supported yet; Unstable; Doesn't follow semver; 🚧

Feel free to create an issue or PR.

## Installation, [npm](https://www.npmjs.com/package/@ahrefs/bs-react-dnd)

```sh
npm install --save @ahrefs/bs-react-dnd
```

Then add `@ahrefs/bs-react-dnd` to `bs-dependencies` in your `bsconfig.json`:

```js
{
  ...
  "bs-dependencies": ["@ahrefs/bs-react-dnd"]
}
```

## TODO

* [ ] DragLayer
* [x] Recreate some examples from react-dnd docs

## Usage

Please take a look at [examples](https://github.com/ahrefs/bs-react-dnd/tree/master/examples).
To run demo:

```sh
$ npm install
$ npm run bs:build
$ npm run server
```
