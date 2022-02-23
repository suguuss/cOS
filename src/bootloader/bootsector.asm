org 0x7C00		; Base adress of the bootloader
				; Shifts the address by the offset of the bootloader
bits 16

KERNEL_ADDR equ 0x8000

; --------------------------------------------------
; ----------------- FAT 32 HEADER ------------------
; --------------------------------------------------
jmp main
db 0x4d, 0x53, 0x44, 0x4F, 0x53, 0x35, 0x2e, 0x30, 0x00, 0x02, 0x01, 0x32, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0xF8, 0x00, 0x00, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x29, 0xF1, 0x4E, 0x48, 0x2E, 0x62, 0x6F, 0x6F, 0x74, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x33, 0x32, 0x20, 0x20, 0x20, 0x0E, 0x1F, 0xBE, 0x77, 0x7C, 0xAC, 0x22, 0xC0, 0x74, 0x0B, 0x56, 0xB4, 0x0E, 0xBB, 0x07, 0x00, 0xCD, 0x10, 0x5E, 0xEB, 0xF0, 0x32, 0xE4, 0xCD, 0x16, 0xCD, 0x19, 0xEB, 0xFE, 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x6E, 0x6F, 0x74, 0x20, 0x61, 0x20, 0x62, 0x6F, 0x6F, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x64, 0x69, 0x73, 0x6B, 0x2E, 0x20, 0x20, 0x50, 0x6C, 0x65, 0x61, 0x73, 0x65, 0x20, 0x69, 0x6E, 0x73, 0x65, 0x72, 0x74, 0x20, 0x61, 0x20, 0x62, 0x6F, 0x6F, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x66, 0x6C, 0x6F, 0x70, 0x70, 0x79, 0x20, 0x61, 0x6E, 0x64, 0x0D, 0x0A, 0x70, 0x72, 0x65, 0x73, 0x73, 0x20, 0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x74, 0x72, 0x79, 0x20, 0x61, 0x67, 0x61, 0x69, 0x6E, 0x20, 0x2E, 0x2E, 0x2E, 0x20, 0x0D, 0x0A, 0x00

; --------------------------------------------------
; --------------------- MAIN -----------------------
; --------------------------------------------------
main:
	; SETTING SOME DEFINES
	CODE_SEG equ GDT_code - GDT_Start
	DATA_SEG equ GDT_data - GDT_Start

	xor ax, ax
	mov es, ax
	mov ds, ax
	mov bp, 0x8000
	mov sp, bp

	mov bx, KERNEL_ADDR		; Where to load the kernel es:bx
	mov dh, 48				; Number of sector to read

	mov ah, 0x02			; Read Sector from drive
	mov al, dh 				; Number of sector to read
	mov ch, 0x00			; Cylinder
	mov dh, 0x00			; Head
	mov cl, 0x02			; Sector nb (Starts at 1)
	int 0x13

	; Clear the screen
	mov ah, 0x0
	mov al, 0x3
	int 0x10                ; text mode

	; --------------------------------------------------
	; ------------ SWITHCING TO PROTECTED MODE ---------
	; --------------------------------------------------
	cli						; Disable the interrupt 
	lgdt [GDT_Descriptor] 	; Loads the GDT

	; Sets Protected Mode bit to 1
	mov eax, cr0 			; cr0 is the control register		
	or  eax, 1				
	mov cr0, eax

	; Jumps to 32 bits segment
	jmp CODE_SEG:start_protected_mode

	jmp $


; --------------------------------------------------
; ------------ GLOBAL DESCRIPTOR TABLE -------------
; --------------------------------------------------
;   https://wiki.osdev.org/Global_Descriptor_Table  
; --------------------------------------------------
GDT_Start:
	GDT_null:
		dq 0		; First entry is null
	GDT_code:
		; base  = 0
		; limit = 0xfffff
		dw 0xffff	; limit bits 0-15
		dw 0		; base  bits 0-15
		db 0		; base  bits 16-23
		db 0x9A		; Access byte
		db 0xCF		; Flags + limit bits 16-19
		db 0		; base 	bits 24-31
	GDT_data:
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

; --------------------------------------------------
; --------------- IN PROTECTED MODE ----------------
; --------------------------------------------------
[bits 32]
start_protected_mode:
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	
	mov ebp, 0x7B00		; 32 bit stack base pointer
	mov esp, ebp

	jmp KERNEL_ADDR

times 510 - ($ - $$) db 0x00
db 0x55, 0xAA