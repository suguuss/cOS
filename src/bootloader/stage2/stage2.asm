org 0x0000
bits 16

; Set blue background and displays "Stage2"
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


; ENTER PROTECTED MODE
; 	Disable interrupts
; 	Enable the A20 line
; 	Load the Global Descriptor Table (GDT)


cli			; Disable the interrupt 




; GLOBAL DESCRIPTOR TABLE
; https://wiki.osdev.org/Global_Descriptor_Table
GDT_Start:
	null:
		dq 0	; First entry is null
	code:
		; base  = 0
		; limit = 0xfffff
		dw 0xffff	; limit bits 0-15
		dw 0		; base  bits 0-15
		db 0		; base  bits 16-23
		db 0x9A		; Access byte
		db 0xCF		; Flags + limit bits 16-19
		db 0		; base 	bits 24-31
	data:
		; base  = 0
		; limit = 0xfffff
		dw 0xffff	; limit bits 0-15
		dw 0		; base  bits 0-15
		db 0		; base  bits 16-23
		db 0x92		; Access byte
		db 0xCF		; Flags + limit bits 16-19
		db 0		; base 	bits 24-31
GDT_End:

GDT_Descriptor:
	dw GDT_End - GDT_Start - 1 	; Size
	dd GDT_Start				; Start

CODE_SEG equ code - GDT_Start
DATA_SEG equ data - GDT_Start


here: 
	hlt
	jmp here