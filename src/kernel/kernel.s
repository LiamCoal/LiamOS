bits 16
org 0x100

jmp _start

print:
    pusha
    mov ah, 0x0E
.lp:
    lodsb
    or cx, cx
    jz .end
    int 10h
    dec cx
    jmp .lp
.end:
    popa
    ret

_start:
    cli
    push es
    push 0x0000
    pop es
    mov word [0x04], keyboardint
    mov word [0x06], 0x0000
    pop es
    sti

keyboardint:
    push es
    push word 0x0001
    pop es
    mov byte [es:0x0000], al
    pop es
    iret
