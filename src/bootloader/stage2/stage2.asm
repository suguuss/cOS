org 0x0000
bits 16

main:
	mov ah, 0x0e ; Enter tty mode
	mov al, 'S'
	int 0x10
	mov al, 't'
	int 0x10
	mov al, 'a'
	int 0x10
	mov al, 'g'
	int 0x10
	mov al, 'e'
	int 0x10
	mov al, '2'
	int 0x10

here: 
	hlt
	jmp here