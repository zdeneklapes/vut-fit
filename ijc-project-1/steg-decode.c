/**
 * steg-decode.c
 * Řešení IJC-DU1, příklad B), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include <stdbool.h>
#include <locale.h>
// #include <limits.h> // inluded in bitset.h

#include "ppm.h"
#include "eratosthenes.h"

int main(int argc, char *argv[])
{
	// program max one argument
	if (argc != 2)
		error_exit("Program vyzaduje jeden argument s nazvem souboru ve formatu ppm");

	// ppm file
	struct ppm *ppmFile = ppm_read(argv[1]);
	// err
	if (ppmFile == NULL)
		error_exit("Soubor se nepovedlo nacist!");

	const bitset_index_t primesUpTo = 3 * ppmFile->xsize * ppmFile->ysize; // data size
	bitset_alloc(primes, primesUpTo);									   // initialize prime pole
	Eratosthenes(primes);

	// steg-decode
	char msg[1] = {0}; // print only one char and then go to next char
	bool end = false;  // help variabel to chech if the string is cancel with '\0'
	for (bitset_index_t i = 23, idx = 0; i < primesUpTo; i++)
	{
		// prime number?
		if (!(bitset_getbit(primes, i)))
		{
			// setbit
			setbit(msg, idx, ppmFile->data[i] & 1);
			// must be here because , because idx & 8 must be == 0
			idx++;

			// end of message
			if (idx > CHAR_BIT - 1 && msg[0] == '\0')
			{
				end = true;
				printf("\n");
				break;
			}

			// print if all bit if char is set; then edx to 0
			else if ((idx % CHAR_BIT) == 0)
			{
				printf("%c", msg[0]);
				idx = 0;
			}
		}
	}

	// dealoc + err
	if (!end)
	{
		bitset_free(primes);
		ppm_free(ppmFile);
		error_exit("Chybny format: Ve zprave nebyl retezec ukoncen znakem '\0' \n");
	}
	// dealoc
	else
	{
		bitset_free(primes);
		ppm_free(ppmFile);
	}

	return 0;
}
