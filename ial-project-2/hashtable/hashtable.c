/*
 * Tabuľka s rozptýlenými položkami
 *
 * S využitím dátových typov zo súboru hashtable.h a pripravených kostier
 * funkcií implementujte tabuľku s rozptýlenými položkami s explicitne
 * zreťazenými synonymami.
 *
 * Pri implementácii uvažujte veľkosť tabuľky HT_SIZE.
 */

// Vypracoval: Zdenek Lapes <xlapes02>

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>

int HT_SIZE = MAX_HT_SIZE;

/*
 * Rozptyľovacia funkcia ktorá pridelí zadanému kľúču index z intervalu
 * <0,HT_SIZE-1>. Ideálna rozptyľovacia funkcia by mala rozprestrieť kľúče
 * rovnomerne po všetkých indexoch. Zamyslite sa nad kvalitou zvolenej funkcie.
 */
int get_hash(char *key) {
	int result = 1;
	int length = strlen(key);
	for (int i = 0; i < length; i++) {
		result += key[i];
	}
	return (result % HT_SIZE);
}

/*
 * Inicializácia tabuľky — zavolá sa pred prvým použitím tabuľky.
 */
void ht_init(ht_table_t *table) {
	for (size_t i = 0; i < MAX_HT_SIZE-1; i++)
	    (*table)[i] = NULL;
}

/*
 * Vyhľadanie prvku v tabuľke.
 *
 * V prípade úspechu vráti ukazovateľ na nájdený prvok; v opačnom prípade vráti
 * hodnotu NULL.
 */
ht_item_t *ht_search(ht_table_t *table, char *key) {
	int index = get_hash(key);
	for (struct ht_item *tmp = (*table)[index]; tmp != NULL; tmp = tmp->next) {
        if (strncmp(tmp->key, key, strlen(key)) == 0)
			return tmp;
	}
	return NULL;
}

/*
 * Vloženie nového prvku do tabuľky.
 *
 * Pokiaľ prvok s daným kľúčom už v tabuľke existuje, nahraďte jeho hodnotu.
 *
 * Pri implementácii využite funkciu ht_search. Pri vkladaní prvku do zoznamu
 * synonym zvoľte najefektívnejšiu možnosť a vložte prvok na začiatok zoznamu.
 */
void ht_insert(ht_table_t *table, char *key, float value) {
	ht_item_t *record = ht_search(table, key);
	int       index   = get_hash(key);  // index to save item on
	size_t    length  = strlen(key)+1;  // length for malloc and memcpy

	if (record == NULL) { // not exist create new record
		if((*table)[index] == NULL) { // first item
			// set item to values + malloc
			if (((*table)[index] = calloc(1, sizeof(struct ht_item))) == NULL)
				return;

			if (((*table)[index]->key = calloc(length, 1)) == NULL)
				return;

			memcpy((char *) (*table)[index]->key, key, length); // need to retype because memset waiting for (char *)
			(*table)[index]->value = value;
			(*table)[index]->next = NULL;
		} else { // second item and this item does not exist
		    ht_item_t *item = NULL;
            if ((item = calloc(1, sizeof (ht_item_t))) == NULL)
                return;

            if ((item->key = calloc(length, 1)) == NULL)
                return;

            // need to retype because memset waiting for (char *)
            memcpy((char *)item->key, key, length);
            item->value = value;
            item->next = (*table)[index];
            (*table)[index] = item;
            return;
//			for (ht_item_t *item = (*table)[index], *prev = item; true ; prev = item) {
//				if((item = item->next) == NULL) {
//					if ((item = calloc(1, sizeof (ht_item_t))) == NULL)
//						return;
//
//					if ((item->key = calloc(length, 1)) == NULL)
//						return;
//
//					// need to retype because memset waiting for (char *)
//					memcpy((char *)item->key, key, length);
//					item->value = value;
//					item->next = NULL;
//					prev->next = item;
//                    return;
//				} // if
//			} // for
		} // if second item
	} else {
		record->value = value; // exist only increment value of occurence
	}
}

/*
 * Získanie hodnoty z tabuľky.
 *
 * V prípade úspechu vráti funkcia ukazovateľ na hodnotu prvku, v opačnom
 * prípade hodnotu NULL.
 *
 * Pri implementácii využite funkciu ht_search.
 */
float *ht_get(ht_table_t *table, char *key) {
    ht_item_t *record = ht_search(table, key);
	return (record) ? &record->value : NULL;
}

/*
 * Zmazanie prvku z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje priradené k danému prvku.
 * Pokiaľ prvok neexistuje, nerobte nič.
 *
 * Pri implementácii NEVYUŽÍVAJTE funkciu ht_search.
 */
void ht_delete(ht_table_t *table, char *key) {
	int index = get_hash(key);

	if ((*table)[index] != NULL) {
        struct ht_item *prev = (*table)[index];
        bool   first  		 = true; // need it because, table[index], must be equal to NULL if key is placed ass the first item

        for (struct ht_item *item = (*table)[index]; item != NULL; prev  = item,
																   item  = item->next,
																   first = false) {
            if (strncmp(item->key, key, strlen(key)) == 0) {
                // prev->next = item->next == NULL ? NULL : item->next; // store the next item to prev item.next pointer
                prev->next = item->next; // store the next item to prev item.next pointer

                memset((char *) item->key, '\0', strlen(item->key)); // delete info
                item->value = 0;

				// free
                free(item->key);
                item->key= NULL;
                free(item);
                item     = NULL;

                if (first)
                    (*table)[index] = NULL;

                return;
            } // if
        } // for
        return;
	} else	// main if
		return;
}

/*
 * Zmazanie všetkých prvkov z tabuľky.
 *
 * Funkcia korektne uvoľní všetky alokované zdroje a uvedie tabuľku do stavu po
 * inicializácii.
 */
void ht_delete_all(ht_table_t *table) {
	for (size_t i = 0; i < HT_SIZE; i++) { // for every slot; and all items in slot
        ht_item_t *tmp = NULL;
        for (ht_item_t *item = (*table)[i]; item != NULL; item = tmp) {
			tmp = item->next; // save next item, because will be free
			memset((char *)item->key, '\0', strlen(item->key)); // delete info
			item->value = 0;

			// free
			free((char *)item->key);
			item->key = NULL;
			free(item);
			item = NULL;
		}
		(*table)[i] = NULL; //	still initialize and alocate but is clear
	}
}
