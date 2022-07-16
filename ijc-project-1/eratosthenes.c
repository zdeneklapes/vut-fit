/**
 * eratosthenes.c
 * Řešení IJC-DU1, příklad A), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "eratosthenes.h"

void Eratosthenes(bitset_t pole)
{
	pole[1] |= 1UL;
	pole[1] |= 1UL << 1;

	// it is needn't do eras for numbers divisible by 2
	for (bitset_index_t i = 2; i * i <= pole[0]; (i + 1) % 2 == 0 ? i += 2 : i++)
		if (!(bitset_getbit(pole, i)))
			for (bitset_index_t j = i + i; j <= pole[0]; j = i + j)
			{
				bitset_setbit(pole, j, 1);
			}
}
