org 0x0000
bits 16

main:
	mov ah, 0		; Set Video Mode
	mov al, 0x03	; Video mode : 80x25
	int 0x10

	mov ah, 0x0B	; Set background color
	mov bh, 0x00	; 
	mov bl, 0x01	; Bleu
	int 0x10 

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