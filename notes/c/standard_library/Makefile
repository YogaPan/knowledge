CC = gcc
CFLAGS = -Wall

EXECUTABLE = $(basename $(wildcard *.c))
.PHONY: all clean

all: $(EXECUTABLE)

tags:
	ctags -R *

clean:
	rm -rf $(EXECUTABLE)
