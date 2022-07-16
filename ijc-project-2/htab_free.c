/**
 * htab_free.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "htab.h"
#include "htab_define.h"

void htab_free(htab_t *t) // destruktor tabulky
{
	htab_clear(t);
	free(t);
}
