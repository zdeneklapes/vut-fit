/**
 * htab_init.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "htab.h"
#include "htab_define.h"

// Položka .arr_size je velikost následujícího pole ukazatelů (použijte
// C99: "flexible array member"). Paměť pro strukturu se dynamicky alokuje
// tak velká, aby se do ní vešly i všechny položky pole.
htab_t *htab_init(size_t n)
{
	htab_t *table = NULL;
	if ((table = malloc(sizeof(htab_t) + (sizeof(struct htab_item *) * n))) == NULL)
    {
	    return NULL;
    }
	else
    {
	    // initilize
        for (size_t i = 0; i < n; i++)
        {
            table->ptrArr[i] = NULL;
        }
        table->size = 0;
        table->arr_size = n;
        return table;
    }
}
