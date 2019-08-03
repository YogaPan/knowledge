CC = gcc
CFLAGS = -Wall
LDFLAGS = -pthread
EXECUTABLES = $(basename $(wildcard *.c))

.PHONY: all clean

all: $(EXECUTABLES)

tags:
	ctags -R *

clean:
	rm -rf $(EXECUTABLES)
