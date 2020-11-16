TITLE Finding a Non Zero Value in an Array (FindNonZero.asm)

; Written by Smilte Valasinaite
;
; This program locates the first nonzero value in the array.
; If none is found, lets ESI point to the sentinel value

INCLUDE Irvine32.inc

.data
array SWORD 50 DUP(?)
sentinel SWORD 0FFFFh

.code
main PROC
	mov esi,OFFSET array 		
	mov ecx,LENGTHOF array 		
L1: 
	cmp WORD PTR [esi],0 	; compare value to zero	
	jnz found 		; jump if value is found
	add esi,2 			
	loop L1 			

	jmp notFound 		; jump if value is not found		

found: 	
	movsx eax,WORD PTR[esi] 
	call WriteInt
	jmp quit

notFound: 	
	movzx eax, sentinel
	call WriteHex
				
quit:		
	call DumpRegs	 
	exit
main ENDP
END main