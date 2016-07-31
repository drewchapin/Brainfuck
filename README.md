![Language](https://img.shields.io/badge/language-C-lightgray.svg)
![Release](https://img.shields.io/github/release/druciferre/brainfuck.svg)
![License](https://img.shields.io/github/license/druciferre/brainfuck.svg?maxAge=2592000)

## Brainfuck


##### DESCRIPTION

This program is an interpretor for the Brainfuck language which was originally
designed by Urban Müller in 1993. Brainfuck is an esoteric programming language,
i.e. a joke. It was designed to challenege and amuse programmers. For a more
complete description of the language see the Wikipedia article at
http://en.wikipedia.org/wiki/Brainfuck

##### COMPILING & INSTALLING THE INTERPRETOR
 
	$ make
	$ sudo make install


##### BASIC COMMANDS
	>    increment the data pointer (to the right)
	<    decrement the data pointer (to the left)
	+    increase (by one) the byte at the current pointer
	-    decrease (by one) the byte at the current pointer
	.    send the byte at the current pointer to stdout
	,    accept one byte of input from the standard input
	[    if the byte at the pointer is zero, then jump to command after next ]
	]    if the byte at the pointer is nonzero, then jump to matching [

##### RUNNING A BRAINFUCK PROGRAM

Save your program as **filename.bf** and run it with

	$ ./brainfuck filename.bf

You can also add a shebang to your script 

	#!/usr/bin/env brainfuck
	[->+<]



