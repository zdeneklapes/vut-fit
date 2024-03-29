
PRJ=c206
#
PROGS=$(PRJ)-test
CC=gcc
CFLAGS=-std=c99 -g -Wall -Wextra -pedantic -lm -fcommon

.PHONY: run clean tests

all: $(PROGS) $(PRJ)-advanced-test

run: $(PROGS) $(PRJ)-test.output
	@./$(PROGS) > current-test.output
	@echo "\nTest output differences:"
	@diff -su $(PROGS).output current-test.output
	@rm -f current-test.output

$(PRJ)-test: $(PRJ).c $(PRJ)-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-test.c

advanced: $(PRJ)-advanced-test $(PRJ)-advanced-test.output
	@./$(PRJ)-advanced-test > current-advanced-test.output
	@echo "\nTest output differences:"
	@diff -su $(PRJ)-advanced-test.output current-advanced-test.output
	@rm -f current-advanced-test.output

$(PRJ)-advanced-test: $(PRJ).c $(PRJ)-advanced-test.c
	$(CC) $(CFLAGS) -o $@ $(PRJ).c $(PRJ)-advanced-test.c

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind-out.txt ./c206-advanced-test

clean:
	rm -f *.o $(PROGS) $(PRJ)-advanced-test
	rm -rfd *.dSYM
#
