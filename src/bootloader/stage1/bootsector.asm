org 0x7C00
bits 16


; FAT32 Header
jmp near main
nop
db 0x4d, 0x53, 0x57, 0x49, 0x4e, 0x34, 0x2e, 0x31, 0x00, 0x02, 0x01, 0x20, 0x00, 0x02, 0x00, 0x00, 0x00, 0x10, 0xF8, 0x00, 0x00, 0x10, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x29, 0xF1, 0x4E, 0x48, 0x2E, 0x62, 0x6F, 0x6F, 0x74, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x46, 0x41, 0x54, 0x33, 0x32, 0x20, 0x20, 0x20, 0x0E, 0x1F, 0xBE, 0x77, 0x7C, 0xAC, 0x22, 0xC0, 0x74, 0x0B, 0x56, 0xB4, 0x0E, 0xBB, 0x07, 0x00, 0xCD, 0x10, 0x5E, 0xEB, 0xF0, 0x32, 0xE4, 0xCD, 0x16, 0xCD, 0x19, 0xEB, 0xFE, 0x54, 0x68, 0x69, 0x73, 0x20, 0x69, 0x73, 0x20, 0x6E, 0x6F, 0x74, 0x20, 0x61, 0x20, 0x62, 0x6F, 0x6F, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x64, 0x69, 0x73, 0x6B, 0x2E, 0x20, 0x20, 0x50, 0x6C, 0x65, 0x61, 0x73, 0x65, 0x20, 0x69, 0x6E, 0x73, 0x65, 0x72, 0x74, 0x20, 0x61, 0x20, 0x62, 0x6F, 0x6F, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x20, 0x66, 0x6C, 0x6F, 0x70, 0x70, 0x79, 0x20, 0x61, 0x6E, 0x64, 0x0D, 0x0A, 0x70, 0x72, 0x65, 0x73, 0x73, 0x20, 0x61, 0x6E, 0x79, 0x20, 0x6B, 0x65, 0x79, 0x20, 0x74, 0x6F, 0x20, 0x74, 0x72, 0x79, 0x20, 0x61, 0x67, 0x61, 0x69, 0x6E, 0x20, 0x2E, 0x2E, 0x2E, 0x20, 0x0D, 0x0A, 0x00


main:
	mov bx, booted
	call WriteString


init_read_disk:
	mov bx, 0x1000		; Loads sector into memory at addr 0x1000:0
	mov es, bx
	mov bx, 0x0
	
	mov dh, 0x0			; head 0
	mov dl, 0x80		; drive 0
	mov ch, 0x0			; cylinder number 0
	mov cl, 3			; Read the 3rd sector (offset 0x400 in hexedit)
	
read_disk:
	mov ah, 0x02 		; int 13/2 : read disk sector
	mov al, 0x01		; nb of sector to read
	int 0x13

	jc error			; if carry bit is 1 -> there is an error

	jmp 0x1000:0		; jumps to where we loaded the second stage 


error:
	mov bx, err_string
	call WriteString

	jmp $

;==============================================================================
; PROCEDURE PrintHex
;
; Description:
;   Prints content of BX in form "0x0000" in teletype mode.
; Inputs:
;   BX: number to print.
; Outputs:
;   No.
;==============================================================================
PrintHex:
    pusha

    mov CX, BX                          ; Save the original number to CX.

    mov SI, .alphabet                   ; Use SI as base for .alphabet array.

    shr BX, 12                          ; Get the first 4 bits of the original number (0x[1]234).
    mov AL, [BX + SI]                   ; Use it as index in the array of hexadecimal digits. Thus get the appropriate character.
    mov [.result + 2], AL               ; Copy the character to the output array.
                                        ; In other words, these instuctions mean result[2] = alphabet[BX].

    mov BX, CX                          ; Restore the original number.
    shr BX, 8                           ; Get the second 4 bits of the original number (0x1[2]34).
    and BX, 0x0F                        ; We have to apply mask 0x0F to the value in order to get exactly 4 bits.
    mov AL, [BX + SI]                   ; AL = alphabet[BX].
    mov [.result + 3], AL               ; result[3] = AL.

    mov BX, CX                          ; Restore the original number.
    shr BX, 4                           ; Get the third 4 bits of the original number (0x12[3]4).
    and BX, 0x0F                        ;
    mov AL, [BX + SI]                   ; AL = alphabet[BX].
    mov [.result + 4], AL               ; result[4] = AL.

    mov BX, CX                          ; Restore the original number.
    and BX, 0x0F                        ; Get the last 4 bits of the original number (0x123[4]).
    mov AL, [BX + SI]                   ; AL = alphabet[BX].
    mov [.result + 5], AL               ; result[5] = AL.

    mov BX, .result                     ; Print the result.
    call WriteString                    ;

    popa
    ret

.alphabet:
    db '0123456789ABCDEF', 0x0

.result:
    db '0x0000', 0x0
;==============================================================================
; PROCEDURE WriteString
;
; Description:
;   Writes a null-terminated string to the screen using BIOS teletype mode text
;   writing.
; Inputs:
;   BX: address of the string.
; Outputs:
;   No.
;==============================================================================
WriteString:
    pusha
    mov SI, 0                           ; Use SI as index in the string.
.loop:
    mov AL, [BX + SI]                   ; Move the current character at the string into AL.

    cmp AL, 0x0                         ; If the current character is null-terminator, then
    je .break                           ; break the loop.

    call WriteCharInTeletypeMode        ; Otherwise print it.

    inc SI                              ; Increment index and
    jmp .loop                           ; jump to the beginning.
.break:
    popa
    ret

;==============================================================================
; PROCEDURE WriteCharInTeletypeMode
;
; Description:
;   Writes a character in teletype mode using BIOS interrupts.
; Inputs:
;   AL: character.
; Outputs:
;   No.
;==============================================================================
WriteCharInTeletypeMode:
    pusha
    mov AH, 0xE                         ; Select BIOS function teletype mode text writing.
    int 0x10
    popa
    ret

booted: db 'Booted', 0x0D, 0x0A, 0
err_string: db 'fail', 0

times 510 - ($ - $$) db 0x00
db 0x55, 0xAA