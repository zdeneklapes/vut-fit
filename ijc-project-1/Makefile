CC = gcc
CFLAGS = -g -O2 -std=c11 -pedantic -Wall -Wextra 
RM = rm -f

#ALL
all: primes primes-i steg-decode steg-encode

# PRIMES
primes: error.o eratosthenes.o primes.o
	$(CC) $(CFLAGS) -o $@ $^

# PRIMES-INLINE
primes-i: error.o eratosthenes-i.o bitset-i.o primes-i.o
	$(CC) $(CFLAGS) -o $@ $^

# STEG-DECODE
steg-decode: error.o eratosthenes.o steg-decode.o ppm.o
	$(CC) $(CFLAGS) -o $@ $^

# STEG-ENCODE
steg-encode: error.o eratosthenes.o steg-encode.o ppm.o
	$(CC) $(CFLAGS) -o $@ $^

# PRIMES MAKRA
error.o: error.c error.h
	$(CC) $(CFLAGS) -c $< -o $@

eratosthenes.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -c $< -o $@

primes.o: primes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -c $< -o $@

# PRIMES INLINE
eratosthenes-i.o: eratosthenes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c eratosthenes.c -o eratosthenes-i.o

bitset-i.o: bitset.h bitset.c
	$(CC) $(CFLAGS) -DUSE_INLINE -c bitset.c -o bitset-i.o

primes-i.o: primes.c eratosthenes.h bitset.h
	$(CC) $(CFLAGS) -DUSE_INLINE -c primes.c -o primes-i.o

# STEG-DECODE
ppm.o: ppm.c ppm.h bitset.h error.h
	$(CC) $(CFLAGS) -c $< -o $@

steg-decode.o: steg-decode.c eratosthenes.h
	$(CC) $(CFLAGS) -c $< -o $@

# STEG-ENCODE
steg-encode.o: steg-encode.c eratosthenes.h
	$(CC) $(CFLAGS) -c $< -o $@

# RUN
.PHONY: run
run: primes primes-i
	ulimit -s 60000; ./primes
	ulimit -s 60000; ./primes-i

# ZIP
.PHONY: zip
zip:
	zip xlapes02.zip *.c *.h Makefile

# CLEAN
.PHONY: clean
clean:
	$(RM) *.o
	$(RM) primes
	$(RM) primes-i
	$(RM) steg-decode
	$(RM) steg-encode
