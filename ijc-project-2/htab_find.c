/**
 * htab_find.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include <ctype.h>

#include "htab.h"
#include "htab_define.h"

htab_pair_t *htab_find(htab_t *t, htab_key_t key) // hledání
{
	uint32_t index = (htab_hash_function(key) % t->arr_size);
	// values in item record
	htab_pair_t *pair = NULL;
	// cyckle through items in index and chech if exist
	for (struct htab_item *record = t->ptrArr[index]; record != NULL; record = record->next)
	{
		if (strncmp(record->item.key, key, strlen(key)) == 0)
		{
			return &record->item;
		}
	}
//	if is not find  -->  return NULL
	return pair;
}
