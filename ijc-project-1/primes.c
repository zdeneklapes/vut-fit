/**
 * primes.c
 * Řešení IJC-DU1, příklad A), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include <stdio.h>
#include <stdbool.h>
#include <time.h>

// #include "bitset.h" //included in eratosthenes
#include "eratosthenes.h"

#define N_BITS (200000000)

void printPrimes(bitset_t bitset)
{
	// print primes
	int countNum = 0;
	const bitset_index_t poleSize = bitset[0];

	// run from the end of array
	for (bitset_index_t i = poleSize - 1;; i--)
	{
		// pokud neni prime skip
		if (!(bitset_getbit(bitset, i)))
			countNum++;

		// if i have all 10 primes then I print them
		if (countNum == 10)
		{
			for (bitset_index_t j = i; j <= poleSize && countNum != 0; j++)
			{
				// run from the smallest priem to the largest prime
				if (!(bitset_getbit(bitset, j)))
				{
					printf("%lu \n", j);
					countNum--;
				}
			}
			return;
		}
	}
}

int main(void)
{
	clock_t start = clock();
	bitset_create(bitset, N_BITS);
	// bitset_alloc(bitset, N_BITS);
	Eratosthenes(bitset);
	printPrimes(bitset);
	// bitset_free(bitset);
	fprintf(stderr, "Time=%.3g\n", (double)(clock() - start) / CLOCKS_PER_SEC);
	return 0;
}
