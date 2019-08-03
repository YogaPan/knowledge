ifeq ($(lock),true)
	CFLAGS := -Wall -std=gnu99 -DUSE_LOCK
else
	CFLAGS := -Wall -std=gnu99 
endif
CC := gcc
LDFLAGS := -pthread
EXEC := $(basename $(wildcard *.c))

.PHONY: all clean

all: $(EXEC)

tags:
	ctags -R *

clean:
	rm -rf $(EXEC)
