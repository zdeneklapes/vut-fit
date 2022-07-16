CC=gcc
CFLAGS=-Wall -g -std=c11 -pedantic -lm
FILES=hashtable.c test.c test_util.c

.PHONY: test clean

all: test_htab

test_htab: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES)

clean:
	rm -f test_htab
	rm -rfd *.dSYM
	rm -f *.log

run_test: clean test_htab
	./test_htab > log_htab.log
	diff -su log_htab.log output_hash_new

valgrind_all: clean all
		 valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out_htab.log ./test_htab
		 grep -i "in use at exit" valgrind-out_htab.log
		@$(MAKE) -s run_test

