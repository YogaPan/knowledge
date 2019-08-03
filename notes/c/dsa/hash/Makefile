CC      := gcc
CFLAGS  := -Wall -std=gnu99 -O2
LDFLAGS :=
OBJS    := hash.o test_hash.o
EXEC    := test_hash

.PHONY: all tags clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CLFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

tags:
	ctags -R --c++-kinds=+p --fields=+iaS --extra=+q .

clean:
	rm -rf $(EXEC) $(OBJS)
