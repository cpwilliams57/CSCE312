// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, the
// program clears the screen, i.e. writes "white" in every pixel.

// Put your code here.

(LOOP)
    @SCREEN
    D=A
    @add
    M=D
    @KBD
    D=M
    @UP
    D;JEQ 
    @DOWN
    0;JEQ 
(DRAW)
    @add
    D=M
    @KBD
    D=D-A
    @LOOP
    D;JEQ
    @c
    D=M
    @add
    A=M
    M=D
    @add
    M=M+1
    @DRAW
    0;JMP
(UP)
    @c
    M=0
    @DRAW
    0;JMP
(DOWN)
   @c
   M=-1
   @DRAW
   0;JMP
