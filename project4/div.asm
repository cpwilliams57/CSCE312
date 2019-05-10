// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/div.asm

// Divides R0 by R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Put your code here.

			//initialize counter variables 
	
	@2
	M=0 	// R2 = 0

(LOOP)
	@0 		
	D=M 	//D = R0
	@1 
	D=D-M  	// D = R0 - R1
	@END
	D;JLT 	//if (RO - R1) < 0 goto END

	@0
	M=D 	// RAM[0] = R0 - R1
	@2 	
	M=M+1	// RAM[2] = RAM[2] + 1
	@LOOP
	0;JMP

(END)
	@END
	0;JMP


