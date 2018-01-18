#!/bin/sh

source /etc/profile.d/32dev.sh

gcc -c kern.c -o kern.o -std=c99 -ffreestanding -O2 -Wall -Wextra &&
    nasm -felf boot.asm -o boot.o &&
    gcc -T linker.ld kern.o boot.o -o os.elf -ffreestanding -O2 -nostdlib -lgcc
    
