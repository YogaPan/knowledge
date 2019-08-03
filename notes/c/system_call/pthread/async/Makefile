CC      := gcc
CFLAGS  := -std=gnu99 -Wall
LDFLAGS :=
OBJS    := async.o async_test.o
EXEC    := async_test

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $^

clean:
	rm -rf $(OBJS) $(EXEC)
