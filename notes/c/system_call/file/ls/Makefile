CC := gcc
CFLAGS = -Wall -std=gnu99 -O2
LDFLAGS :=
EXEC := ls

all: $(EXEC)

$(EXEC): ls.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf $(EXEC)
