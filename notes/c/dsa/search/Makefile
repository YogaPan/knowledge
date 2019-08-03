CC := gcc
CFLAGS = -Wall -std=gnu99 -O2
LDFLAGS :=
EXEC = binary_search

.PHONY: all clean

all: binary_search

binary_search: binary_search.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(EXEC)
