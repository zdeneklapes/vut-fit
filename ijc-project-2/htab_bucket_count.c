/**
 * htab_bucket_count.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "htab.h"
#include "htab_define.h"

size_t htab_bucket_count(const htab_t *t) // velikost pole
{
    return t->arr_size;
}
