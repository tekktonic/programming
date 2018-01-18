    section .multiboot_header
head_start:
    dd 0xe85250d6
    dd 0
    dd head_end - head_start
    ;;  the checksum
    dd 0x100000000 - (0xe85250d6 + (head_end - head_start))

    dw 0
    dw 0
    dd 8
head_end:  
