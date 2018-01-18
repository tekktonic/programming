all:
	ca65 -t vic20 --listing hello.asm -o hello.o
	ld65 -C linker.ld hello.o -o hello
	xvic ./hello
