TITLE Reversing a String Using POP and PUSH (RevStr2.asm)

; Written by Smilte Valasinaite
;
; This program prints the original string, reverses it, 
; places it into the second array and prints it as well

INCLUDE Irvine32.inc

.data 
original BYTE "This is the original string", 0
reverse BYTE SIZEOF original DUP(0), 0

.code
main PROC
	mov esi, 0
	mov ecx, SIZEOF original-1

L1:
	movzx eax, original[esi]
	push eax
	inc esi
	loop L1
	
	mov esi, 0
	mov ecx, SIZEOF original-1

L2:
	pop eax
	mov reverse[esi], al
	inc esi 	
	loop L2

	call DumpRegs
	mov edx, OFFSET original
	call WriteString
	call Crlf
	mov edx, OFFSET reverse
	call WriteString
	exit
main ENDP
END main