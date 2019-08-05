bits 16
org 0x7c00

_start:	
	mov si, bgnmsg
	mov cx, 20
	call print
	jmp $

print:
	mov ah, 0x0e
	mov bx, 0
.lp0:
	lodsb
	or cx, cx
	jz .return
	int 10h
	dec cx
	jmp .lp0
.return: ret

bgnmsg: db `Starting LiamOS...\r\n`