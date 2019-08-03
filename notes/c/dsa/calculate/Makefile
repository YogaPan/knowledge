CC = gcc
CFLAGS = -Wall
EXECUTABLES = $(basename $(wildcard *.c))

all: $(EXECUTABLES)

tags:
	ctags -R *

clean:
	rm -rf $(EXECUTABLES)
