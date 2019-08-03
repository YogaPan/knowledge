CC      = gcc
CFLAGS  = -Wall -std=gnu99 -O2
LDFLAGS = -pthread
OBJS    = $(patsubst %.o,%.c,$(wildcard *.c))

all: get

get: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

tags:
	ctags -R *

clean:
	rm -rf get
