/**
 * steg-encode.c
 * Řešení IJC-DU1, příklad B), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "ppm.h"
#include "eratosthenes.h"
// #include "error.h"

int main(int argc, char *argv[])
{
	// program must have one argument
	if (argc != 2)
		error_exit("Program vyzaduje jeden argument s nazvem souboru ve formatu ppm");

	// ppm file load
	struct ppm *ppmFile = ppm_read(argv[1]);
	// test if OK
	if (ppmFile == NULL)
		error_exit("Zprava nebyla zapsana!");

	// size to alloc
	const unsigned long primesUpTo = 3 * ppmFile->xsize * ppmFile->ysize;
	// primes
	bitset_alloc(primes, primesUpTo);
	Eratosthenes(primes);

	// encode
	char msg[] = "Toto je testovaci zprava pro ppmfile\n\0";
	for (bitset_index_t i = 23, idx = 0; i < primesUpTo; i++)
	{
		if (!(bitset_getbit(primes, i)))
		{
			setbit_encode(ppmFile->data, i, getbit(msg, idx));
			idx++;
		}
	}

	// write data to file
	ppm_write(argv[1], ppmFile);

	// dealoc
	bitset_free(primes);
	ppm_free(ppmFile);

	printf("Zprava zapsana!\n");
	return 0;
}
