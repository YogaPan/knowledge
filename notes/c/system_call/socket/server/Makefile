CC      = gcc
CFLAGS  = -Wall -std=gnu99
LDFLAGS = -pthread
OBJS    = $(patsubst %.c,%.o,$(wildcard *.c))

server: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

tags:
	ctags -R *

clean:
	rm -rf $(OBJS)
