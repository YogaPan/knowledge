CC = gcc
CFLAGS = -Wall
LDFLAGS = -lcurses

all: demo

demo: demo.c
	$(CC) $(CFLAGS) demo.c -o demo $(LDFLAGS)

clean:
	rm -rf demo *.o
