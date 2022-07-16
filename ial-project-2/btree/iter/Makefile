CC=gcc
CFLAGS=-Wall -g -std=c11 -pedantic -lm
FILES=btree.c ../btree.c stack.c ../test_util.c ../test.c

.PHONY: test clean

all: test_iter

test_iter: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

clean:
	rm -f test_iter
