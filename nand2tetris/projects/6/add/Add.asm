// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
						// by Nisan and Schocken, MIT Press.
  // File name: projects/6/add/Add.asm

// Computes R0 = 2 + 3  (R0 refers to RAM[0])

(RANDOM_LABEL)
//@2
D=A      // hahahah wesh
//@3
D=D+A
//@0
M=D;jmp
//tests
//@sum
M=D
//@R0
M=d
//@KBD
M+1
//@RANDOM_LABEL
M=D
