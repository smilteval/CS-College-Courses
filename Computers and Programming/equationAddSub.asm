TITLE Solving an Equation (Equation.asm)

; Written by Smilte Valasinaite
;
; This program solves an equation:
; RVAL=(XVAL-YVAL)-(ZVAL+3+XVAL)-10–ZVAL

INCLUDE Irvine32.inc

.data 
RVAL WORD ?
XVAL WORD 1
YVAL WORD 2
ZVAL WORD 3

.code
main PROC
	; clearing eax and ebx
	mov eax, 0
	mov ebx, 0
	
	; (XVAL-YVAL)
	mov ax, XVAL
	sub ax, YVAL
	
	; (ZVAL+3+XVAL)
	mov bx, ZVAL
	add bx, 3
	add bx, XVAL

	; (XVAL-YVAL)-(ZVAL+3+XVAL)-10–ZVAL
	sub ax, bx
	sub ax, 10
	sub ax, ZVAL

	; place the result in RVAL
       	mov RVAL, ax

	call DumpRegs
	exit
main ENDP
END main