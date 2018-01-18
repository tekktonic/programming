#!/bin/sh

nasm -f elf -l fizz.lst -g fizz.asm -o fizz.o
ld -m elf_i386 -g fizz.o -o fizz
