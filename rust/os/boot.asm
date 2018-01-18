%define screen 0xb8000
    global start

    section .text
    bits 32
start:
    mov esp, stack_top

    call verify_boot
    call verify_cpu
    call verify_64bit
    
    mov dword [0xb8000], 0x2f4b2f4f
    hlt


verify_cpu:
    pushfd
    pop eax

    mov ecx, eax

    ;;  grab ID bit
    xor eax, 1 << 21
    push eax
    popfd

    pushfd
    pop eax

    push ecx
    popfd

    cmp eax, ecx
    je nocpu
    ret

nocpu:
    mov al, "0"
    jmp error


verify_64bit:
    ;; check if we have extended info
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb no_64bit

    ;;  check if we have 64bit support
    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz no_64bit
    ret
no_64bit:
    mov al, "6"
    jmp error
verify_boot:
    cmp eax, 0x36d76289
    jne boot_fail
    ret
boot_fail:
    mov al, "8"
    jmp error
    
error:
    mov dword [screen], 0x4f524f45
    mov dword [screen+4], 0x4f3a4f52
    mov dword [screen+8], 0x4f204f20
    mov byte [screen+10], al
    hlt


    section .bss
stack_bottom:
    resb 64
stack_top:  
