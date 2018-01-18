[bits 32]
%define stdout 1
%define syscall int 0x80
section .bss
	x resd 1			;2 words
	i resb 2
	spaces resd 1

section .data
	fizz db "fizz", $00
	fizz_len equ $ - fizz
	buzz db "buzz"
	buzz_len equ $ - buzz
	space db " ", $00
	newline db $0A, $00

section .text
	global main
	global _start

main:
_start:
	mov ebx, 5
	call spaceit
	mov eax, 4
	mov ebx, stdout
	mov ecx, fizz
	mov edx, fizz_len
	syscall
	mov eax, 4
	mov ebx, stdout
	mov ecx, newline
	mov edx, 2
	syscall
	
	mov eax, 1
	mov ebx,0
	syscall



print:
	push eax
	push ebx
	
	mov eax, 4
	mov ebx, stdout
	syscall
	pop ebx
	pop eax

	ret
f:
	push ecx
	push edx
	mov ecx, fizz
	mov edx, fizz_len
	call print
	pop ecx
	pop edx
	ret
b:
	push ecx
	push edx
	mov ecx, buzz
	mov edx, buzz_len
	call print
	pop ecx
	pop edx
	ret
spaceit:
	push eax
	push ecx
	push edx
	mov eax, 0

spaceit_loop:	
	cmp ebx,eax
	je spaceit_end
	mov ecx, space
	mov edx, 1
	call print
	sub ebx,1
	jmp spaceit_loop
spaceit_end:
	pop eax
	pop ecx
	pop edx
	ret
