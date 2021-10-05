; CSI-370 Assignment 5.2, Ethan Heil

extern ExitProcess : proc

.DATA
sentence BYTE "Assembly is the best programming language!", 0		; Create sentence variable
aCount	 QWORD 0		; Counter for # of 'a's
x		 QWORD 0		; Loop Counter
len		 QWORD 43		; Length of the sentence

.CODE

_main PROC


mov rax, len		; Move the value of len into rax
mov x, rax			; Move the value of rax into x

mov rdx, OFFSET sentence	; Move the starting address of sentence into rdx

forloop:
	
	movzx rdi, BYTE PTR [rdx]	; Move the current character into rdi (zero extend)
	cmp rdi, 'A'				; Check if current character is 'A' -> (if rdi - ascii value of 'A' == 0, then this character is an 'A')
	jz letterFound				; Jump to letterFound if the result of cmp is 0

	cmp rdi, 'a'				; Check if current character is 'a' -> (if rdi - ascii value of 'a' == 0, then this character is an 'a')
	jz letterFound				; Jump to letterFound if the result of cmp is 0

	progressLoop:
		dec x					; Decrement loop counter
		inc rdx					; Increment rdx register to get the next character in the string
		cmp x, 0				; Check if the loop counter is 0
		jne forloop				; Jump to the top of the loop if the counter is not 0
		jmp done				; Jump to done if loop is finished

letterFound:
	mov rsi, aCount				; Move the value of aCount into rsi
	inc rsi						; Increment the rsi register
	mov aCount, rsi				; Move the value in rsi to aCount
	jmp progressLoop			; Jump back into the loop
	
done:
xor rcx, rcx
call ExitProcess
_main ENDP
END