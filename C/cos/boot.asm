	;; multiboot header
MBALIGN equ 1<<0
MEMINFO equ 1<<1
FLAGS equ MBALIGN | MEMINFO
MAGIC equ 0x1badb002
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
	align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .boostrap_stack
align 4
stack_bottom:
	times (16*1024) db 0
stack_top:

section .text
global _start
_start:
	mov esp, stack_top
	extern kmain
	call kmain

	cli
.hang:
	hlt
	jmp .hang
