CC = gcc
CFLAGS = -Wall -Werror
LDFLAGS = -lm -pthread

exec = $(basename $(wildcard *.c))

.PHONY: all clean

all: $(exec)

tags:
	ctags -R *

clean:
	@rm -rf $(exec)
