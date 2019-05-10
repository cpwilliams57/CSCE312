//This asm computes the modulo of two numbers
//Assuming R0 stores the number a and R1 stores the number b (b can not be 0)
//so in normal programming language, the goal is to compute RAM[R0]%RAM[R1]
//The result will be put to RAM[R2]
//Assuming RAM[R1] is positive integer and RAM[R0] is non-negative integer
//write your code here.
	
	@0
	D = M
	@2	
	M = D
	@temp
	M = D

(LOOP)
	@temp 		
	D=M 	//D = R0
	@1 
	D=D-M  	// D = R0 - R1
	@END
	D;JLT 	//if (RO - R1) < 0 goto END

	@2 	
	M=D	
	@temp
	M = D
	@LOOP
	0;JMP

(END)
	@END
	0;JMP
