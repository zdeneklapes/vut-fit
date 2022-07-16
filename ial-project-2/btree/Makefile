C=gcc
SANIT=-fsanitize=address
CFLAGS=-Wall -g -std=c11 -pedantic -lm
FILES_REC =rec/btree.c  btree.c              test_util.c test.c
FILES_ITER=iter/btree.c btree.c iter/stack.c test_util.c test.c

.PHONY: test_iter test_rec clean

all: test_iter test_rec 

test_iter: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES_ITER)

test_rec: $(FILES)
	$(CC) $(CFLAGS) -o $@ $(FILES_REC)

clean:
	rm -f   test_rec test_iter
	rm -rfd *.dSYM
	rm -f *.log

test: clean all 
	./test_rec  > log_rec.log
	./test_iter > log_iter.log
	diff -su log_rec.log log_iter.log
	diff -su log_rec.log btree.out
	diff -su log_iter.log btree.out

valgrind_all: test
		 valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out_iter.log \
         ./test_iter
		 valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out_rec.log \
         ./test_rec
		 grep -i "in use at exit" valgrind-out_iter.log
		 grep -i "in use at exit" valgrind-out_rec.log
		@$(MAKE) -s test

		

