// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

(MAIN_LOOP)
@KBD
D=M 

@BLACKEN
D;JGT 
@WHITEN
0;JMP

(BLACKEN)
@SCREEN 
D=A
@addr
M=D 

(BLACK_LOOP)
@addr
D=M
@24576  // End of memory + 1
D=D-A
@MAIN_LOOP
D;JEQ  // if addr == 24576 ? we're done

@addr
A=M
M=-1   // blacken current word 
@addr
M=M+1 // Move to next address

@BLACK_LOOP
0;JMP

(WHITEN)
@SCREEN
D=A 
@addr 
M=D

(WHITE_LOOP)
@addr
D=M 
@24576
D=D-A 
@MAIN_LOOP
D;JEQ 

@addr 
A=M 
M=0
@addr 
M=M+1 
@WHITE_LOOP
0;JMP
