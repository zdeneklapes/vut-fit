/**
 * htab_move.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "htab.h"
#include "htab_define.h"

htab_t *htab_move(size_t n, htab_t *from) // přesun dat do nové tabulky
{
//    initilize
    htab_t *t2 = htab_init(n);
    size_t size = htab_bucket_count(from);
//    must to iterate in from table indexes
    for (size_t i = 0; i < size; i++)
    {
//        for every item in this index; create a new table with different index
        for (struct htab_item *item = from->ptrArr[i]; item != NULL; item = item->next)
        {
            htab_pair_t *pair = htab_lookup_add(t2, item->item.key);
            pair->value = item->item.value;
        }
    }
//    reset *from table
    htab_clear(from);
    return t2;
}

