CC = gcc
CFLAGS = -Wall
EXECUTABLES = $(basename $(wildcard *.c))

.PHONY: all clean

all: $(EXECUTABLES)

tags:
	ctags -R *

clean:
	rm -rf $(EXECUTABLES)
