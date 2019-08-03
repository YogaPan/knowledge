CC = gcc
CFLAGS = -Wall

all: hello embed_asm

hello: hello.o
	ld hello.o -o hello

hello.o: hello.S
	$(CC) -c hello.S

tags:
	ctags -R *

clean:
	rm -rf hello hello.o
