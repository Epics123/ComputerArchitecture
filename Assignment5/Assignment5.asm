; CSI-370 Assignment 5.2 Ethan Heil

extern ExitProcess : proc

.DATA
sentence BYTE "Assembly is the best programming language!", 0		; Create sentence variable
aCount	 QWORD ?		; Counter for # of 'a's
x		 QWORD 0		; Loop Counter

.CODE

_main PROC

mov x, 43


xor rcx, rcx
call ExitProcess
_main ENDP
END