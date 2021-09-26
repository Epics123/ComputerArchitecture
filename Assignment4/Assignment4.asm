; CSI-370 Assignment 4.2 Ethan Heil

extrn ExitProcess : proc

.DATA
score1 QWORD 25							; score for test 1
score2 QWORD 89							; score for test 2
score3 QWORD 49							; score for test 3
score4 QWORD 80							; score for test 4

total1 QWORD 30							; total points for test 1
total2 QWORD 100						; total points for test 2
total3 QWORD 50							; total points for test 3
total4 QWORD 150						; total points for test 4

possiblePoints QWORD ?					; maximum possible points
pointsScored QWORD ?					; total number of points the student scored
percentage QWORD ?						; student's overall percentage

.CODE

_main PROC
	
	mov rax, 0							; clear data in rax
	mov rax, score1						; move score1 into rax
	add rax, score2						; add rax and score2: (score 1 + score2)
	add rax, score3						; add rax and score3: (score1 + score2) + score3
	add rax, score4						; add rax and score4: (score1 + score2 + score3) + score 4
	mov pointsScored, rax				; move the value in rax to pointsScored

	mov rax, 0							; clear data in rax
	mov rax, total1						; move score1 into rax
	add rax, total2						; add rax and score2: (score 1 + score2)
	add rax, total3						; add rax and score3: (score1 + score2) + score3
	add rax, total4						; add rax and score4: (score1 + score2 + score3) + score 4
	mov possiblePoints, rax				; move the value in rax to pointsScored

	mov rdx, 100						; move decimal value 100 to rdx
	mov rax, pointsScored				; move the value of pointsScored into rax
	mul rdx								; multiply  100 * points scored

	mov rdx, 0							; move 0 into rdx
	mov rcx, possiblePoints				; move the value of possible points into rcx
	div rcx								; divide rax by rcx - (100 * pointsScored) / possiblePoints to get the percentage as a whole number

	mov percentage, rax					; assign the value in rax to percentage

xor rcx, rcx
call ExitProcess
_main ENDP
END