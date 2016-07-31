CC=gcc

default: brainfuck

brainfuck.o: brainfuck.c
	$(CC) -Wall -c brainfuck.c -o brainfuck.o

brainfuck: brainfuck.o
	$(CC) brainfuck.o -o brainfuck

install: brainfuck
	install -m 0755 brainfuck /usr/local/bin

uninstall:
	-rm -f /usr/local/bin/brainfuck
	
clean:
	rm -f brainfuck.o
	rm -f brainfuck
