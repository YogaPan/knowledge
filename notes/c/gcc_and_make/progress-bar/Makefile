CC = gcc
CFLAGS = -Wall
EXEC = main

.PHONY: all clean install remove

all: $(EXEC)

main: libprogress.a test_progress.c
	$(CC) $(CFLAGS) $^ -o $@ -L./

libprogress.a: progress.o str.o
	ar -cvq $@ $^

progress.o: progress.c progress.h
	$(CC) $(CFLAGS) $^ -c

str.o: str.c str.h
	$(CC) $(CFLAGS) $^ -c

tags:
	ctags -R *

clean:
	rm -rf *.o *.a *.gch $(EXEC) tags
