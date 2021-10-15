; Assignment 6.1, Ethan Heil

getInput PROTO
printResult PROTO

.DATA
num1 DWORD 0;
num2 DWORD 0;
result DWORD 0;

.CODE

asmMain PROC
	; Shadow Space
	push rbp
	push rdi
	sub rsp, 20h
	lea rbp, [rsp + 20h]

	; Get input from C++ functions
	call getInput
	mov num1, eax
	call getInput
	mov num2, eax

	; Call Sum
	movsxd rcx, num1
	movsxd rdx, num2
	call _sum

	; Set result to sum's return value
	mov result, eax

	;  Call printResult in C++
	movsxd rcx, result
	call printResult

	; Clean up stack and exit function
	xor rcx, rcx
	lea rsp, [rbp]
	pop rdi
	pop rbp
	ret
asmMain ENDP

_sum PROC
	; Shadow Space
	push rbp
	push rbx
	sub rsp, 20h
	lea rbp, [rsp + 20h]

	; Add function parameters
	mov rax, rcx
	add rax, rdx

	; Clean up stack and exit function
	lea rsp, [rbp]
	pop rbx
	pop rbp
	ret
_sum ENDP

END