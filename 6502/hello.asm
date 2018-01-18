    .org $0fff
    .word $1001                 ;start of the BASIC program
	.word start-2               ; redundancy?
	.word $0001                 ; BASIC line
	.byte $9e                   ; SYS
	.byte "4109"                ;4109, start
	.byte 0, 0, 0               ; end of BASIC

start:
    ;; lda #$4A
    ;; jsr $FFD2
    lda #$b0
    sta $a0
    lda #$04
    sta $a1
    jsr print

    brk

print:
    .proc Print                 ; create Print namespace
    ldx #$00
loop:
    lda ($a0,x)
    cmp #$0
    beq done
    lda ($a0,x)
    jsr $FFD2
    inx
    jmp loop
done:
    rts
    .endproc                    ;Print
    

.segment "DATA"
msg: .byte "Hello there this is an awfully long string that should be easy to catch shouldn't it?", $00
    
printbuf:    .res 256, $00
