CC = gcc
CFLAGS = -Wall

EXEC = $(basename $(wildcard *.c))
.PHONY: all clean

all: $(EXEC)

tags:
	ctags -R *

clean:
	rm -rf $(EXEC)
