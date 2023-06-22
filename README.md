# Melange bindings for react-dnd

[Melange](https://melange.re) bindings for [react-dnd](https://github.com/react-dnd/react-dnd).

## Status

🚧 Not everything is supported yet; Unstable; Doesn't follow semver; 🚧

Feel free to create an issue or PR.

## Install

Install [opam](https://opam.ocaml.org/) package manager.

Then:

```
opam pin add melange-react-dnd.dev git+https://github.com/ahrefs/melange-react-dnd.git#master
```

The bindings support the following versions of the `react-dnd` and `react-dnd-html5-backend`
npm packages, which should be installed separately, together with `react` and `react-dom`:

```json
  "dependencies": {
    "react": "^18.2.0",
    "react-dom": "^18.2.0",
    "react-dnd": "^14.0.3",
		"react-dnd-html5-backend": "^14.0.1"
  }
```

# Setup

Add `melange-react-dnd` to the `libraries` in your `dune` file:

```dune
; ...
  (libraries melange-react-dnd)
; ...
```


## TODO

* [ ] DragLayer
* [x] Recreate some examples from react-dnd docs

## Usage

Please take a look at [examples](https://github.com/ahrefs/melange-react-dnd/tree/master/examples).
To run demo:

Run `make watch` for Melange compiler watcher.

Run `make serve` to interact with the example in the browser (`localhost:8080`).
