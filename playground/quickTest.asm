// Compute sum of 1 to n, where n is in RAM[0]
@0
D=M
@n
M=D       // n = RAM[0]
@i
M=1       // i = 1
@sum
M=0       // sum = 0

(LOOP)
@i
D=M
@n
D=D-M
@END
D;JGT     // if i > n, goto END

@sum
D=M
@i
D=D+M     // D = sum + i
@sum
M=D       // sum = sum + i
@i
M=M+1     // i = i + 1
@LOOP
0;JMP

(END)
@sum
D=M
@0
M=D       // Store result in RAM[0]
@END
0;JMP
