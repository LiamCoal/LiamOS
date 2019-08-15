bits 16
org 0x7c00

jmp start

print:
    pusha
    mov ah, 0x0E
.lp:
    lodsb
    or al, al
    jz .end
    int 10h
    jmp .lp
.end:
    popa
    call refreshcursor
    ret

println:
    call print
    mov ah, 0x0E
    mov al, ' '
    mov bh, 0x00
    int 10h
    mov si, newline
    call print
    ret

refreshcursor:
    mov ah, 0x0E
    mov al, '_'
    mov bl, 0x0F
    int 10h

    mov ah, 0x03
    int 10h

    mov ah, 0x02
    mov bh, 0
    dec dl
    int 10h

    ret

sleep:
    or ecx, ecx
    jz .end
    dec ecx
    nop
    jmp sleep
.end:
    ret

start:
    mov ah, 00h
    mov al, 13h
    int 10h

    mov si, kernmsg
    mov bl, 0x0A
    call println

    cli
    mov word [0x200], int80h
    mov word [0x202], cs
    sti

    mov si, int80h_donemsg
    mov bl, 0x09
    mov eax, 0
    int 80h

    

    jmp $

int80h:
    cmp eax, 0
    je .println
    cmp eax, 1
    je .print
    cmp eax, 2
    je .geterr
    cmp eax, 3
    je .sleep
    jmp .error
.println:
    call println
    jmp .exit
.print:
    call print
    jmp .exit
.geterr:
    mov al, byte [0x0FFF]
    mov byte [0x0FFF], 0
    jmp .exit
.sleep:
    call sleep
.error:
    mov al, byte [0x0FFF]
    or al, 00000010b
.exit:
    iret

kernmsg: db `LIAMOS KERNEL 1.0`,0
newline: db `\r\n`,0
int80h_donemsg: db `Set int 80h successfully`,0
moduleload_donemsg: db `Done`