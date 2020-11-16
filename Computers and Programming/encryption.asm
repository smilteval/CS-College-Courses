TITLE Encrypting a String (Encryption.asm)

; Written by Smilte Valasinaite
;
; This program gets input message from the user,
; then encrypts it and displays the encrypted message, 
; and then decrypts it and displays the decrypted message

INCLUDE Irvine32.inc

KEY = 174
MAX = 128

.data
promptText BYTE "Enter the plain text: ", 0
encryptionText BYTE "Cipher text: ", 0
decryptionText BYTE "Decrypted: ", 0
array BYTE MAX+1 DUP(0)
arraySize DWORD ?

.code 
main PROC
	mov edx, OFFSET promptText
	call WriteString

	call GetInput			
	call Translate
	
	mov edx, OFFSET encryptionText
	call WriteString
	mov edx, OFFSET array
	call WriteString
	call Crlf

	call Translate

	mov edx, OFFSET decryptionText
	call WriteString
	mov edx, OFFSET array
	call WriteString
	
	exit
main ENDP

GetInput PROC 
	; prompts user to input a message and saves its size

	mov ecx, MAX
	mov edx, OFFSET array
	call ReadString
	mov arraySize, eax	
	ret
GetInput ENDP

Translate PROC
	; translates the string with the encryption key

	mov ecx, arraySize
	mov esi, 0
L1:
	xor array[esi],KEY
	inc esi
	loop L1
	
	ret
Translate ENDP

END main


