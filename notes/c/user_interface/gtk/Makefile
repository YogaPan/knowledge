CC := gcc
CFLAGS := -Wall -std=gnu99
LDFLAGS := `pkg-config --cflags --libs gtk+-2.0`

.PHONY: all clean

all: hello

hello: hello.c
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -rf hello
