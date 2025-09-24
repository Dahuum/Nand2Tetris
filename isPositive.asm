// Check RAM[0] is positive

@0
D=M

@POSITIVE
D;JGT

@1
M=0

@END
0;JMP

(POSITIVE)
M=1
@end 

(END)
@END
0;JMP
