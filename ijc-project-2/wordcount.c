/**
 * wordcount.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

/******************************************************************************/
/*** TODO ***/
/******************************************************************************/

/******************************************************************************/
/*** INCLUDE ***/
/******************************************************************************/
#include "htab.h"
#include "htab_define.h"
#include "io.h"

/******************************************************************************/
/*** MACRO ***/
/******************************************************************************/
#define MAX_WORD 127

// Table size jsem vybral tak, aby nedochazelo prilis casto ke kolizim slov se
// stejnym indexem a zaroven aby nebylo zabrano prilis mnoho mista na disku
// zaroven jsem zvazil aby TABLE_SIZE bylo prvocislo kvuli vhodnejsimu vysledku
// pri deleni
#define TABLE_SIZE 30211

/******************************************************************************/
/*** FUNCTIONS ***/
/******************************************************************************/
void myPrint(htab_pair_t *pair)
{
    fprintf(stdout, "%s\t%d\n", pair->key, pair->value);
}

#ifdef HASHTEST
size_t htab_hash_function(const char *str)
{
    uint32_t h = 0; // musí mít 32 bitů
    const unsigned char *p;
    for (p = (const unsigned char *)str; *p != '\0'; p++)
    {
        h = 65555 * h + *p;
    }
    return h;
}
#endif

/******************************************************************************/
/*** MAIN ***/
/******************************************************************************/
int main()
{
	FILE *f = stdin;
    htab_t *table = NULL;
    char *s = NULL;
//  init table; for saving word from *f;
	if ((table = htab_init(TABLE_SIZE)) == NULL)
	{
	    goto error1;
	}
//	init s; for reading words from stdin
	if ((s = calloc(MAX_WORD+1, 1))== NULL)
	{
	    goto error1;
	}

    int size = 0;
//	must be condition "&& i > 0" because it can return EOF
    for (int i; (i = read_word(s, MAX_WORD, f)) != EOF;)
    {
//	    set size; if return size from read_word is greater than actual size, set new value; for the print statement about warning and max char
        size = (i > size) ? i : size;
//	    if null alocation failed and exit()
        if (htab_lookup_add(table, s) == NULL)
        {
            goto error1;
        }
//      reset *s for next word
        memset(s, '\0', MAX_WORD);
    }
    if (size == MAX_WORD)
    {
        fprintf(stderr, "Slovo je delsi nez: %d znaku (proto bylo zkraceno)! Nasledujici slova se zkrati na max: %d znaku!\n", MAX_WORD, MAX_WORD);
    }

    void (*printPtr)(htab_pair_t *) = myPrint;

#ifdef MOVETEST
    htab_t *tmp;
    if ((tmp = htab_move(100, table)) == NULL)
    {
        goto error1;
    }
    htab_free(table);
    if ((table = htab_move(5, tmp)) == NULL)
    {
        htab_free(tmp);
        goto error1;
    }
    htab_free(tmp);
    htab_for_each(table, printPtr);
#else
    htab_for_each(table, printPtr);
#endif // MOVETEST
//  free *s for read_word
    free(s);
//  free table and all its slots
    htab_free(table);
    return 0;

	error1:
	    fprintf(stderr,"Alokace selhala!");
	    if (s != NULL)
        {
            free(s);
        }
	    if (table != NULL)
        {
            htab_free(table);
        }
        return 1;
}
