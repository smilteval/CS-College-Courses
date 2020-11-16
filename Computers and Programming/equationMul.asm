TITLE Solving an Equation using SHIFT (Equation.asm)

; Written by Smilte Valasinaite
;
; This program solves the equation:
; eax = (ebx * 20) / ecx 

INCLUDE Irvine32.inc

.code
main PROC
	; giving initial values to ebx and ecx
	mov ebx, 2
	mov ecx, 4
	
	; (ebx * 20)
	mov edx, ebx
	shl ebx, 4
	shl edx, 2
	add ebx, edx
	
	; (ebx * 20) / ecx
	shr ebx, 2

	; place the result in eax
	mov eax, ebx

	call dumpregs
	call writeint 
	exit
main ENDP
END main
