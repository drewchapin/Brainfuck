/*
 * Brainfuck Interpreter
 *   Copyright (C) 2007  Drew Chapin <druciferre@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE	5000		//how big should the memory be?

char *stack,		//array of bytes for the program to modify
	*p;	//pointer to current position in stack

unsigned int size = 0;	//stores the size of the program

int parse( const char * );	//prototype for the parser
char *getfile( const char * );	//prototype to get the contents of the file
int help();			//prototype to print help

int main( int argc, char **argv )
{

	int a = 1;	// keeps track of current argument
	char *program; // used to load brainfuck program into memory

	if( argc <= 1 )	// show help if no arguments
		return help();

	//check if any of the arguments are help arguments
	while( a++ < (argc-1) )	// run through the arguments
		if( strcmp("--h",argv[a]) == 0 || strcmp("--help",argv[a]) == 0 )
			return help();

	//allocate the stack
	stack = (char*) malloc(STACKSIZE);

	//go through all of the arguments and open the file and run them
	//or accept input from the standard input and run it
	//note: this allows you do something like ./brainfuck hello.bf -
	//it will execute hello.bf and then accept standard input and
	//the interpreter will clear the stack and reset the pointer after
	//each argument
	a = 0;
	while( (argc-1) > a++ )
		if( strcmp("-",argv[a]) == 0 )
		{
			// allocate enough space to store the program
			program = (char*) malloc(STACKSIZE);
			memset( program, size=0, STACKSIZE );
			
			//reset the stack
			memset( stack, 0, STACKSIZE);
			p = stack;

			// read standard input until we reach the end of the file
			// allocate STACKSIZE bytes to start with, if we get close to that
			// allocate STACKSIZE more bytes to play with
			while( (program[size++]=getchar()) != EOF )
				if( size >= STACKSIZE-1 )
					program = realloc(program, size+STACKSIZE );
			program[size-1] = '\0'; //make the EOF char null
			parse( program ); // execute the program
		}
		else
		{
			// allocate enough space to store the program
			program = getfile( argv[a] );
			
			//reset the stack
			memset( stack, 0, STACKSIZE);
			p = stack;
			
			parse( program ); // execute the program
		}

	free( stack );
	free( program );

	return 0;

}

int help()
{
	printf( "Usage: brainfuck [FILE]...\n" );
	printf( "Interpreter for the Brainfuck language which was originally designed by Urban Müller in 1993. Brainfuck is an esoteric programming language, i.e. a joke. It was designed to challenege and amuse programmers\n\n" );
	printf( "  --h, --help\tdisplay this help and exit\n\n" );
	printf( "Examples: \n  brainfuck hello.bf\trun hello.bf\n  brainfuck -\t\trun instructions from standard input\n" );
	
	return 0;
}

char *getfile( const char *path )
{
	FILE *f = fopen( path, "r" );
	char *input, *line = NULL;
	size_t len = 0;
	ssize_t read; 

	if( !f )
	{
		printf( "\nError: Could not open file '%s'\n", path );
		exit( 1 );
	}
	else
	{
		
		// read first line
		read = getline( &line, &len, f );

		// seek to end and get size of program
		fseek( f, 0, SEEK_END );
		size = ftell(f);

		// rewind to beginning of file or first instruction (skip shebang)
		if( read > 2 && line[0] == '#' && line[1] == '!' )
			fseek( f, read, SEEK_SET );
		else
			rewind( f );
		
		// allocate space to store program
		input = (char*)malloc(size);
		memset( input, 0, size );
		
		//read the program into memory
		fread( input, 1, size, f );
		fclose( f );

		return input;
	}
}

int parse( const char *program )
{

	int	c = 0, // current instruction position1
		d = 0, //current instruction for inside loops
		level = 0; //embedded loop level
	
	char *temp; //subloops

	#ifdef __DEBUG__	
	printf( "\ndebug: program = '%s'\n", program );
	#endif
	
	while( c < strlen(program) )
	{
		switch( program[c++] )
		{
			case '>': 
				++p; 
				#ifdef __DEBUG__
				printf( "\ndebug: ++p = %p\n", p );
				#endif
				break;
			case '<': 
				--p; 
				#ifdef __DEBUG__
				printf( "\ndebug: --p = %p\n", p );
				#endif
				break;
			case '+': 
				++*p; 
				#ifdef __DEBUG__
				printf( "\ndebug: ++*p = %d\n", *p );
				#endif
				break;
			case '-': 
				--*p; 
				#ifdef __DEBUG__
				printf( "\ndebug: --*p = %d\n", *p );
				#endif
				break;
			case '.': 
				putchar( *p ); 
				#ifdef __DEBUG__
				printf( "\ndebug: putchar( %d );\n", *p );
				#endif
				break;
			case ',': 
				*p = getchar();
				#ifdef __DEBUG__
				printf( "\ndebug: getchar() = '%d';\n", *p );
				#endif
				break;
			case '[': 

				temp = (char*) malloc( strlen(program)  );
				memset( temp, 0, strlen(program) ); 

				d = 0;
				level++;

				while( level > 0 && c < strlen(program) )
				{
					if( program[c] == '[' )
						level++;
					else if( program[c] == ']' )
						level--;
					else
						temp[d++] = program[c];
					c++;
				}
				
				while( *p != 0 && *p != '\0' )
					parse( temp );
				break;
			case ']': 
				fputs( "\nError: The brackets are unbalanced.\n", stderr );
				exit( 1 );
				break;
		}
		
		if( p < stack || p > stack + STACKSIZE )
		{
			fputs( "\nError: Range error.\n", stderr );
			exit( 1 );
		}
	}
}
