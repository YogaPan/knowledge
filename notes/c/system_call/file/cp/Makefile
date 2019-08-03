CC := gcc
CFLAGS := -Wall -std=gnu99 -O2
LDFLAGS :=
EXEC := cp

all: $(EXEC)

$(EXEC): cp.c
	$(CC) $(CFLAGS) $^ -o $@ $(CFLAGS)

clean:
	rm -rf $(EXEC)
