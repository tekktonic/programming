section .text
	global _start
	global _main
main:	
_start:	
itoa:	
	mov eax, 1234
	mov ebx, 0
	mov ecx, $0A
	div ecx
	add edx, $30
	mov [scratch+ebx], edx
	add ebx, 1
	mov [scratch+ebx], byte 0
	mov eax, 4
	mov ebx, 1
	mov ecx, scratch
	mov edx, 2
	int 0x80

	mov eax, 1
	mov ebx, 0
	int 0x80
section .bss
	scratch resb 5
