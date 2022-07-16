CC=gcc
CFLAGS=-Wall -g -std=c11 -pedantic -lm
FILES=btree.c ../btree.c ../test_util.c ../test.c

.PHONY: test_rec clean

all: test_rec

test_rec: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

clean:
	rm -f test
