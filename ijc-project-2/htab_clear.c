/**
 * htab_clear.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include <string.h>

#include "htab.h"
#include "htab_define.h"

void htab_clear(htab_t *t) // ruší všechny záznamy
{
    size_t size = t->arr_size;
	// for every slot; and all items in slot
	for (size_t i = 0; i < size; i++)
	{
        struct htab_item *tmp = NULL;
		for (struct htab_item *item = t->ptrArr[i]; item != NULL; item = tmp)
        {
//		    save next item
			tmp = item->next;
//			delete info
			memset((char *)item->item.key, '\0', strlen(item->item.key));
			item->item.value = 0;
//			free key;   must set NULL, value after dealocate stay untouched
			free((char *)item->item.key);
			item->item.key = NULL;
//			free item
			free(item);
			item = NULL;
		}
//		still initialize and alocate but is clear
        t->ptrArr[i] = NULL;
	}
	t->size = 0;
}

