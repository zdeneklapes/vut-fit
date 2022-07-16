/**
 * htab_define.h
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>

#ifndef __HTAB_DEFINE__
#define __HTAB_DEFINE__

#include "htab.h"

struct htab_item
{
	htab_pair_t item;
	struct htab_item *next;
};

struct htab
{
	size_t size;
	size_t arr_size;
	struct htab_item *ptrArr[];
};

#endif // __HTAB_DEFINE__
