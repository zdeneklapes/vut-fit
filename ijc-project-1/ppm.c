/**
 * ppm.c
 * Řešení IJC-DU1, příklad B), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include <string.h>
#include "ppm.h"

#define DATA_LIMIT (3 * 8000 * 8000)

#define ERROR_WAR(f, text) \
	fclose(f);             \
	warning_msg(text);     \
	return NULL;

#define ERROR_EXIT(f, text) \
	fclose(f);              \
	error_exit(text);

struct ppm *ppm_read(const char *filename)
{
	FILE *f = fopen(filename, "rb");
	char fileType[3] = {0};
	unsigned int width = 0, heigth = 0, RGBColor = 0;

	// file open ok/err?
	if (f == NULL)
	{
		ERROR_EXIT(f, "Soubour nejde otevrit!");
	}

	// file type load
	if (fgets(fileType, sizeof(fileType), f) == NULL)
	{
		ERROR_EXIT(f, "chybny format");
	}

	// file type check
	if (strcmp(fileType, "P6") != 0)
	{
		ERROR_EXIT(f, "chybny format");
	}

	// width, height
	if (fscanf(f, "%u %u", &width, &heigth) != 2)
	{
		ERROR_WAR(f, "chybny format, velikosti se nepodarilo nacist");
	}

	// RGBColor
	if (fscanf(f, "%u", &RGBColor) != 1 || RGBColor != 255)
	{
		ERROR_WAR(f, "chybny format, RGBColor musi byt '255' !")
	}

	// go to end of line
	while (fgetc(f) != '\n')
		;

	// data size
	bitset_index_t sizeToAlloc = 3 * heigth * width;
	if (sizeToAlloc > DATA_LIMIT)
	{
		ERROR_WAR(f, "Data na alokaci jsou prilis velka!");
	}

	// Alocation
	struct ppm *ppmFile = malloc(sizeof(struct ppm) + sizeToAlloc);
	if (ppmFile == NULL)
	{
		ERROR_WAR(f, "Alokace se nezdarila!")
	}
	else
	{
		ppmFile->xsize = width;
		ppmFile->ysize = heigth;
	}

	// data
	if (fread(ppmFile->data, sizeof(char), sizeToAlloc, f) != sizeToAlloc)
	{
		free(ppmFile);
		ERROR_EXIT(f, "Data se nepodarilo nacist");
	}

	fclose(f);
	return ppmFile;
}

void ppm_write(const char *filename, struct ppm *ppmFile)
{
	// open file
	FILE *f = fopen(filename, "wb");

	// specification of file
	fprintf(f, "P6\n");
	fprintf(f, "%d %d\n", ppmFile->xsize, ppmFile->ysize);
	fprintf(f, "255\n");

	// data size
	unsigned long sizeData = 3 * ppmFile->xsize * ppmFile->ysize;
	if (sizeData > DATA_LIMIT)
	{
		warning_msg("Moc dat na zapis");
		fclose(f);
		return;
	}

	// pixel data
	if (fwrite(ppmFile->data, sizeof(char), sizeData, f) != sizeData)
		warning_msg("Do souboru se nepodarilo zapsat data");

	fclose(f);
}

void ppm_free(struct ppm *p)
{
	free(p);
}
