section .text
	global _start
	global main

main:
_start:
	mov edx, namelen
	mov ecx, name
	mov eax, 4
	int 0x80

	mov ebx, 3
	jmp tabloop
	;;  hello section

tabloop:
	cmp ebx, 0
	je endtabloop
	mov edx, tablen
	mov ecx, tab
	mov eax, 4
	int 0x80
	dec ebx
	jmp tabloop
endtabloop:
	ret
	;; empty

	call printhello
	call newline


	
	mov ebx, 2
	call tabloop
	call printhello
	mov ebx, 1
	call tabloop
	call printhello
	call newline


	
	mov ebx, 1
	call tabloop
	call hello
	mov ebx, 1
	call tabloop
	call hello
	mov ebx, 1
	call tabloop
	call hello
	call newline


	
	mov ebx, 2
	call tabloop
	call hello
	mov ebx, 1
	call tabloop
	call hello
	call newline

	mov ebx, 1
	call tabloop
	call hello
	call newline
	call newline

	mov eax, 4
	mov edx, 2
	mov ecx, bye
	int 0x80
	

printhello:	
	mov edx,hellolen
	mov ecx,hello
	mov eax, 4
	int 0x80
	ret

newline:
	mov edx, nllen
	mov ecx, nl
	mov eax, 1
	int 0x80
	ret
	
section .data
	name db "My name is Daniel Wilkins", $0A, 0
	namelen equ $ - name
	hello db "Hello", 0
	hellolen equ $ - hello

	tab db 09, 0
	tablen equ 2
	nl db $0A, 0
	nllen equ tablen
	
	bye db "Bye", 0
	byelen equ $ - bye
