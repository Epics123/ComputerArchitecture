; Assignment 8.1, Ethan Heil

_getDouble PROTO
_printString PROTO
_printDouble PROTO

.DATA
r REAL8 ?
h REAL8 ?
V REAL8 ?
tmp QWORD ?

.CODE

_asmMain PROC
	; Shadow Space
	push rbp
	sub rsp, 20h
	lea rbp, [rsp + 20h]

	call _getDouble
	movsd r, xmm0 

	call _getDouble
	movsd h, xmm0

	;Calculate r^2
	fld r
	fld r
	fmul ST(0), ST(1)

	;Multiply r^2 and h
	fld h
	fmul ST(0), ST(1)

	;Multiply by pi
	fldpi
	fmul ST(0), ST(1)

	fstp V
	movsd xmm0, V

	call _printDouble

	lea rsp, [rbp]
	pop rbp
	ret
_asmMain ENDP

END