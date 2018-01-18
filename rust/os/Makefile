kernel.iso: iso/kernel.bin
	grub-mkrescue -o kernel.iso iso
iso/kernel.bin: boot.o multiboot.o
	ld -n -o iso/kernel.bin -T linker.ld multiboot.o boot.o
boot.o: boot.asm
	nasm -felf64 boot.asm -o boot.o

multiboot.o: multiboot.asm
	nasm -felf64 multiboot.asm -o multiboot.o
