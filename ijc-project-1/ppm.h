/**
 * ppm.h
 * Řešení IJC-DU1, příklad B), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#ifndef PPM_H
#define PPM_H

#include <stdio.h>
#include "bitset.h"
#include "error.h"

struct ppm
{
	unsigned xsize;
	unsigned ysize;
	char data[]; // RGB bajty, celkem 3*xsize*ysize
};

struct ppm *ppm_read(const char *filename);
void ppm_write(const char *filename, struct ppm *ppmFile);
void ppm_free(struct ppm *p);

#endif // PPM_H
