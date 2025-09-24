// let's add an asm code
// it add the RAM[0] RAM[1] to
//      RAM[2]

@0
D=M

@1
D=D+M

@2
M=D

@6
0;JMP

