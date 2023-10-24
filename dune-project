(lang dune 3.8)

(using melange 0.1)

(name melange-react-dnd)

(generate_opam_files)

(package
 (name melange-react-dnd)
 (synopsis "Melange bindings for react-dnd")
 (description "Melange bindings for react-dnd JavaScript library.")
 (maintainers "Liubomyr Mykhalchenko <liubomyr.mykhalchenko@ahrefs.com>")
 (authors "Liubomyr Mykhalchenko <liubomyr.mykhalchenko@ahrefs.com>")
 (tags
  (melange react-js org:ahrefs))
 (homepage https://github.com/ahrefs/melange-react-dnd/)
 (documentation https://github.com/ahrefs/melange-react-dnd/)
 (bug_reports https://github.com/ahrefs/melange-react-dnd/issues)
 (license MIT)
 (source
  (github ahrefs/melange-react-dnd))
 (depends
  (melange
   (>= 2.0.0))
  (reason
   (>= 3.10.0))
  reason-react
  reason-react-ppx
  (melange-webapi :with-test) ;  # used to build the examples
  (ocaml-lsp-server :with-dev-setup)
  (opam-check-npm-deps :with-dev-setup)))
