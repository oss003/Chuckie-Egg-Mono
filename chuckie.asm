asm_code         equ $2b00

;********************************************************************
; Header for Atom emulator Wouter Ras

             org asm_code-22
name_start
		 .db "CH-EGG"                    ; 16 bytes filename
name_end
             .blkb (16-name_end+name_start),0
		 .dw asm_code                     ; 2 bytes startaddress
		 .dw asm_code                     ; 2 bytes linkaddress
		 .dw eind_asm-start_asm           ; 2 bytes filelength

;********************************************************************

start_asm          
		include chuckie.inc
		include font.inc
		include sound.inc
		include joystick.inc
eind_asm
