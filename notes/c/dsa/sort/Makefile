CC     = gcc
CFLAGS = -Wall -std=gnu99 -DRANDOM_FILE='"./random.txt"' -DARRAY_SIZE=5000
OBJS   = $(subst %.c,%.o,$(wildcard *.c))
EXEC   = test_time

.PHONY: all random clean plot

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^

tags:
	ctags -R *

plot:
	python3 ./scripts/generate.py && ./test_time && python3 ./scripts/plot.py

clean:
	rm -rf *.txt *.png $(EXEC)
