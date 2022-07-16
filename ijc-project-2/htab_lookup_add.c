/**
 * htab_lookup_add.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include <stdlib.h>

#include "htab.h"
#include "htab_define.h"

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key)
{
	// find record return NULL if not exist
	htab_pair_t *record = htab_find(t, key);
	// index to save item on
	uint32_t index = (htab_hash_function(key) % t->arr_size);
//  length for malloc and memcpy
    size_t length = strlen(key)+1;
    // not exist create new record
	if (record == NULL)
	{
//	    first item
        if(t->ptrArr[index] == NULL)
        {
            // set item to values + malloc
            if ((t->ptrArr[index] = calloc(1, sizeof(struct htab_item))) == NULL)
            {
                return NULL;
            }
            if ((t->ptrArr[index]->item.key = calloc(length, 1)) == NULL)
            {
                return NULL;
            }
//		need to retype because memset waiting for (char *)
            memcpy((char *) t->ptrArr[index]->item.key, key, length);
            t->ptrArr[index]->item.value++;
            t->ptrArr[index]->next = NULL;
            t->size++;
            // return added item
            return &t->ptrArr[index]->item;
        }
//      second item and this item does not exist
        else
        {
            for (struct htab_item *item = t->ptrArr[index], *prev = item; true ; prev = item)
            {
                if((item = item->next) == NULL)
                {
                    if ((item = calloc(1, sizeof (struct htab_item))) == NULL)
                    {
                        return NULL;
                    }
                    if ((item->item.key = calloc(length, 1)) == NULL)
                    {
                        return NULL;
                    }
//		            need to retype because memset waiting for (char *)
                    memcpy((char *)item->item.key, key, length);
                    item->item.value++;
                    item->next = NULL;
                    t->size++;
//                  set thw new item
                    prev->next = item;
                    return &item->item;
                }
            }
        }
	}
	else
	{
		// exist only increment value of occurence
		record->value++;
        return record;
	}
}
