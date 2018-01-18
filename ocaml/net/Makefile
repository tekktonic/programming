all: httpget

httpget: httpget.ml
	ocamlfind ocamlopt -o httpget -linkpkg -package netclient httpget.ml

clean:
	rm *.o *.cmx *.cmi httpget
