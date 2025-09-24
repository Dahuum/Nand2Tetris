// fill array with -1

@50
D=A 
@arr 
M=D 
@10
D=A 
@n
M=D
@i 
M=0

(LOOP)
@i 
D=M 
@n
D=D-M 
@END 
D;JEQ   // if i == n goto END

@arr 
D=M 
@i 
D=D+M // D = arr + i (current address)
A=D   // Set A to current address 
M=-1

@i 
M=M+1 
@LOOP 
0;JMP

@END 
0;JMP
