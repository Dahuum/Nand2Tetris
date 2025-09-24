// Swap RAM[0] and RAM[1] using @temp var

@0
D=M 

@temp   // kayn f RAM[16], vars are automaticlly allocated starting from RAM[16]
M=D	   // temp == RAM[0]

@1
D=M   // D = RAM[1]

@0
M=D  // RAM[0] == RAM[1]

@temp
D=M    // D == temp

@1
M=D 

@12
0;JMP
