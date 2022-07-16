#! /bin/sh

# STEG-DECODE
make clean
make steg-decode
valgrind --leak-check=full -v --track-origins=yes ./steg-decode du1-obrazek.ppm

# PRIMES
# make clean
# make
# valgrind --leak-check=full -v --track-origins=yes ./primes