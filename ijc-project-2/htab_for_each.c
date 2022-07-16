/**
 * htab_for_each.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "htab.h"
#include "htab_define.h"

// for_each: projde všechny záznamy a zavolá na ně funkci f
void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data))
{
    size_t size = htab_bucket_count(t);
    // print every slot and its item.next
    for (size_t i = 0; i < size; i++)
    {
        for (struct htab_item *item = t->ptrArr[i]; item != NULL; item = item->next)
        {
            f(&item->item);
        }
    }
}
