CC := gcc
CFLAGS := -Wall -std=gnu99
LDFALGS :=
OBJS := test.o binary_tree.o
EXEC := test

all: $(EXEC)

$(EXEC): binary_tree.o test.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

binary_tree.o: binary_tree.c binary_tree.h
	$(CC) $(CFLAGS) $^ -c

test.o: test.c binary_tree.h
	$(CC) $(CFLAGS) $^ -c

clean:
	rm -rf $(EXEC)
