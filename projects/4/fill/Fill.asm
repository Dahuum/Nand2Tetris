// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

//A Register: Holds addresses or constants.
//D Register: General-purpose data register.
//M Register: Refers to memory location addressed by A register.

//Jump Conditions :

//JGT: Jump if greater than zero.
//JEQ: Jump if equal to zero.
//JGE: Jump if greater than or equal to zero.
//JLT: Jump if less than zero.
//JNE: Jump if not equal to zero.
//JLE: Jump if less than or equal to zero.
//JMP: Unconditional jump (always jump).

@loop  // Load the address of the loop label
0;JMP  // Unconditional jump to the loop label

(LOOP) // Hada houa likansmiouh LOOP LABEL
@KBD
D=M
@FILL_SCREEN
D;JNE
@CLEAR_SCREEN
0;JMP

(FILL_SCREEN)
@SCREEN
D=A // D == 16384 (start of screen memory)
(FILL_LOOP)
A=D
M=-1
D=D+1
@SCREEN_END
D=D-A
@FILL_LOOP
D;JGT
@LOOP
0;JMP

(CLEAR_SCREEN)
@SCREEN
D=A
(CLEAR_LOOP)
A=D 
M=0
D=D+1
@SCREEN_END
D=D-A 
@CLEAR_LOOP
D;JLT
@LOOP
0;JMP

(SCREEN_END)
@24576