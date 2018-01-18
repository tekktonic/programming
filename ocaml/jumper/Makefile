all: jumper

jumper: main.ml
	ocamlfind ocamlopt -strict-sequence -linkpkg -package sdl,sdl.sdlimage main.ml -o jumper
