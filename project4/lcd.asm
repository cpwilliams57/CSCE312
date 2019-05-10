//Using Euclidean algorithm to find the larget common divisor of two non-negative integers
//Assuming RAM[R0] stores the first integer and RAM[R1] stores the second integer
//RAM[R2] stores the result
//Write your code here

@0
D=M
@1
D=D-M
@IF_TRUE
D;JLT		//if (R0 - R1) < 0 goto IF_TRUE

@0
D=M
@a
M=D 		// a = R0

@1
D=M
@b
M=D 		//b = R1

@c
M=1

@WRITE
0;JMP

(IF_TRUE)	//if (R0 - R1) < 0 was true
	@0
	D=M
	@b
	M=D 		//b = R0

	@1
	D=M
	@a
	M=D 		//a = R1

(WRITE)
	@b
	D=M
	@ZERO
	D;JEQ		//If b = 0 go to ZERO

(OLOOP)
	@c
	@END
	D;JEQ

(ILOOP)
	@a
	D=M
	@b
	D=D-M
	@IEND
	D;JLT

	@a
	M=D
	@c
	M=D
	@ILOOP
	0;JMP
(IEND)
	@b
	D=M
	@a
	M=D

	@c
	D=M
	@b
	M=D

	@OLOOP
	0;JMP



(ZERO)			//if b = 0, R2 = a 
	@a	
	D=M
	@2
	M=D
	@END
	0;JMP

(END)
	@a
	D=M
	@2
	M=D

	@END
	0;JMP




