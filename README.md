![license](https://img.shields.io/github/license/druciferre/brainfuck.svg?maxAge=2592000)
![GitHub release](https://img.shields.io/github/release/druciferre/brainfuck.svg)

## Brainfuck


##### DESCRIPTION

This program is an interpretor for the Brainfuck language which was originally
designed by Urban Müller in 1993. Brainfuck is an esoteric programming language,
i.e. a joke. It was designed to challenege and amuse programmers. For a more
complete description of the language see the Wikipedia article at
http://en.wikipedia.org/wiki/Brainfuck

##### COMPILING THE INTERPRETOR
 Linux & GCC

    gcc -o2 -o brainfuck brainfuck.c


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

    ./brainfuck filename.bf
