/**
 * htab_erase.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include <ctype.h>
#include "htab.h"
#include "htab_define.h"

bool htab_erase(htab_t *t, htab_key_t key) // ruší zadaný záznam
{
    // find record return NULL if not exist
    htab_pair_t *record = htab_find(t, key);

	// item exist
	if (record != NULL) {
        // index to save item on
        uint32_t index = (htab_hash_function(key) % t->arr_size);
        struct htab_item *prev = t->ptrArr[index];
//       need it because, t.ptrArr[index], must be equal to NULL if key is placed ass the first item
        bool first = true;

        for (struct htab_item *item = t->ptrArr[index]; item != NULL; prev = item, item = item->next, first = false) {
            if (strncmp(item->item.key, key, strlen(key)) == 0) {
//               store the next item to prev item.next pointer
                prev->next = item->next == NULL ? NULL : item->next;

//			    delete info
                memset((char *) item->item.key, '\0', strlen(item->item.key));
                item->item.value = 0;

//			    free(need to do that because free only dealocat ememory but value is stay untouched)
                free((char *) item->item.key);
                item->item.key = NULL;
                free(item);
                item = NULL;

                if (first)
                {
                    t->ptrArr[index] = NULL;
                }

                t->size--;
                return true;
            }
        }
//      somewhere err
        return false;
	}
	// not exist
	else
	{
		return false;
	}
}
