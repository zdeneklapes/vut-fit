/**
 * htab_size.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "htab.h"
#include "htab_define.h"

size_t htab_size(const htab_t *t) // počet záznamů v tabulce
{
	return t->size;
}
