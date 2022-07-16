
/* ******************************* c206.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c206 - Dvousměrně vázaný lineární seznam                            */
/*  Návrh a referenční implementace: Bohuslav Křena, říjen 2001               */
/*  Vytvořil: Martin Tuček, říjen 2004                                        */
/*  Upravil: Kamil Jeřábek, září 2020                                         */
/*           Daniel Dolejška, září 2021                                       */
/* ************************************************************************** */
/*
** Implementujte abstraktní datový typ dvousměrně vázaný lineární seznam.
** Užitečným obsahem prvku seznamu je hodnota typu int. Seznam bude jako datová
** abstrakce reprezentován proměnnou typu DLList (DL znamená Doubly-Linked
** a slouží pro odlišení jmen konstant, typů a funkcí od jmen u jednosměrně
** vázaného lineárního seznamu). Definici konstant a typů naleznete
** v hlavičkovém souboru c206.h.
**
** Vaším úkolem je implementovat následující operace, které spolu s výše
** uvedenou datovou částí abstrakce tvoří abstraktní datový typ obousměrně
** vázaný lineární seznam:
**
**      DLL_Init ........... inicializace seznamu před prvním použitím,
**      DLL_Dispose ........ zrušení všech prvků seznamu,
**      DLL_InsertFirst .... vložení prvku na začátek seznamu,
**      DLL_InsertLast ..... vložení prvku na konec seznamu,
**      DLL_First .......... nastavení aktivity na první prvek,
**      DLL_Last ........... nastavení aktivity na poslední prvek,
**      DLL_GetFirst ....... vrací hodnotu prvního prvku,
**      DLL_GetLast ........ vrací hodnotu posledního prvku,
**      DLL_DeleteFirst .... zruší první prvek seznamu,
**      DLL_DeleteLast ..... zruší poslední prvek seznamu,
**      DLL_DeleteAfter .... ruší prvek za aktivním prvkem,
**      DLL_DeleteBefore ... ruší prvek před aktivním prvkem,
**      DLL_InsertAfter .... vloží nový prvek za aktivní prvek seznamu,
**      DLL_InsertBefore ... vloží nový prvek před aktivní prvek seznamu,
**      DLL_GetValue ....... vrací hodnotu aktivního prvku,
**      DLL_SetValue ....... přepíše obsah aktivního prvku novou hodnotou,
**      DLL_Previous ....... posune aktivitu na předchozí prvek seznamu,
**      DLL_Next ........... posune aktivitu na další prvek seznamu,
**      DLL_IsActive ....... zjišťuje aktivitu seznamu.
**
** Při implementaci jednotlivých funkcí nevolejte žádnou z funkcí
** implementovaných v rámci tohoto příkladu, není-li u funkce explicitně
 * uvedeno něco jiného.
**
** Nemusíte ošetřovat situaci, kdy místo legálního ukazatele na seznam
** předá někdo jako parametr hodnotu NULL.
**
** Svou implementaci vhodně komentujte!
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

// Vypracoval: Zdeněk Lapeš <xlapes02>

#include "c206.h"

int error_flag;
int solved;

/**
 * Vytiskne upozornění na to, že došlo k chybě.
 * Tato funkce bude volána z některých dále implementovaných operací.
 */
void DLL_Error() {
	printf("*ERROR* The program has performed an illegal operation.\n");
	error_flag = TRUE;
}

/**
 * Provede inicializaci seznamu list před jeho prvním použitím (tzn. žádná
 * z následujících funkcí nebude volána nad neinicializovaným seznamem).
 * Tato inicializace se nikdy nebude provádět nad již inicializovaným seznamem,
 * a proto tuto možnost neošetřujte.
 * Vždy předpokládejte, že neinicializované proměnné mají nedefinovanou hodnotu.
 *
 * @param list Ukazatel na strukturu dvousměrně vázaného seznamu
 */
void DLL_Init( DLList *list ) {
	if (list) {
		list->activeElement = NULL;
		list->firstElement = NULL;
		list->lastElement = NULL;
	}
}

/**
 * Zruší všechny prvky seznamu list a uvede seznam do stavu, v jakém se nacházel
 * po inicializaci.
 * Rušené prvky seznamu budou korektně uvolněny voláním operace free.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Dispose( DLList *list ) {
	DLLElementPtr tmpPtr = NULL; // elem to delete
	while(list->firstElement) {
		tmpPtr = list->firstElement; 
		list->firstElement = list->firstElement->nextElement; // firstElem will be deleted -> so we need to udpate firstElem
		free(tmpPtr);
		tmpPtr = NULL; // after free -> ptr have unexpected value -> give to it NULL value is good
	}

	// set it as after DLL_Init
	list->firstElement  = NULL;
	list->lastElement   = NULL;
	list->activeElement = NULL;
}

/**
 * Vloží nový prvek na začátek seznamu list.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na začátek seznamu
 */
void DLL_InsertFirst( DLList *list, int data ) {
	// allocate mem
	DLLElementPtr MyDLLElementPtr = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (!MyDLLElementPtr) {
		DLL_Error();
		return;
	}

	// init newElem
	MyDLLElementPtr->data = data;
	MyDLLElementPtr->nextElement= list->firstElement;
	MyDLLElementPtr->previousElement= NULL;

	if (list->firstElement != NULL) { 	// list not empty
		list->firstElement->previousElement = MyDLLElementPtr;
	} else { 							// list is empty
		list->lastElement = MyDLLElementPtr;
	}

	list->firstElement = MyDLLElementPtr;
}

/**
 * Vloží nový prvek na konec seznamu list (symetrická operace k DLL_InsertFirst).
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení na konec seznamu
 */
void DLL_InsertLast( DLList *list, int data ) {
	// aloc mem
	DLLElementPtr MyDLLElementPtr = (DLLElementPtr)malloc(sizeof(struct DLLElement));
	if (!MyDLLElementPtr) {
		DLL_Error();
		return;
	}

	// init newElem
	MyDLLElementPtr->data = data;
	MyDLLElementPtr->nextElement= NULL;
	MyDLLElementPtr->previousElement= list->lastElement;

	if (list->lastElement != NULL) { 	// list is not empty
		list->lastElement->nextElement = MyDLLElementPtr;
	} else {							// list is empty
		list->firstElement 			= MyDLLElementPtr;
	}

	list->lastElement = MyDLLElementPtr;
}

/**
 * Nastaví první prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz (nepočítáme-li return),
 * aniž byste testovali, zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_First( DLList *list ) {
	list->activeElement = list->firstElement;
}

/**
 * Nastaví poslední prvek seznamu list jako aktivní.
 * Funkci implementujte jako jediný příkaz (nepočítáme-li return),
 * aniž byste testovali, zda je seznam list prázdný.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Last( DLList *list ) {
	list->activeElement = list->lastElement;
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu prvního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetFirst( DLList *list, int *dataPtr ) {
	if (list->firstElement)	{ // list is not empty
		*dataPtr = list->firstElement->data;
	} else { // empty
		DLL_Error();
	}
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu posledního prvku seznamu list.
 * Pokud je seznam list prázdný, volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetLast( DLList *list, int *dataPtr ) {
	if (list->firstElement)	{ // list is not empty
		*dataPtr = list->lastElement->data;
	} else { // empty
		DLL_Error();
	}
}

/**
 * Zruší první prvek seznamu list.
 * Pokud byl první prvek aktivní, aktivita se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteFirst( DLList *list ) {
	DLLElementPtr tmpPtr; // elem to delete

	if (list->firstElement) {
		if (list->activeElement == list->firstElement) { // nothing to do
			list->activeElement = NULL;
		}
		if (list->firstElement == list->lastElement) { // list has one elem
			free(list->firstElement);
			list->firstElement = NULL;
			list->lastElement = NULL;
		} else { 									   // now I can delete firstElem
			tmpPtr = list->firstElement->nextElement;
			free(list->firstElement);
			list->firstElement = tmpPtr;
		}
	}
}

/**
 * Zruší poslední prvek seznamu list.
 * Pokud byl poslední prvek aktivní, aktivita seznamu se ztrácí.
 * Pokud byl seznam list prázdný, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteLast( DLList *list ) {
	DLLElementPtr tmpPtr;

	if (list->lastElement) {
		if (list->activeElement == list->lastElement) { // nothing to do
			list->activeElement = NULL;
		}
		if (list->firstElement == list->lastElement) { // list has one elem
			free(list->lastElement);
			list->firstElement = NULL;
			list->lastElement  = NULL;
		} else {								// now I can delete lastElem
			tmpPtr = list->lastElement->previousElement;
			tmpPtr->nextElement = NULL;
			free(list->lastElement);
			list->lastElement = tmpPtr;
		}
	}
}

/**
 * Zruší prvek seznamu list za aktivním prvkem.
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * posledním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteAfter( DLList *list ) {
    DLLElementPtr tmpPtr = NULL;

	if (list->activeElement) { // list must be active
		// activeElem can't be last
		if (list->activeElement->nextElement) {
            if (list->activeElement->nextElement == list->lastElement) { // last but one
                tmpPtr = list->activeElement->nextElement;
                list->activeElement->nextElement = NULL;
                list->lastElement = list->activeElement;
            } else { // somewhere in middle od start of list
                tmpPtr = list->activeElement->nextElement;
                list->activeElement->nextElement = tmpPtr->nextElement;
				tmpPtr->nextElement->previousElement = list->activeElement;
			}
            free(tmpPtr);
            tmpPtr = NULL;
        }
	}
}

/**
 * Zruší prvek před aktivním prvkem seznamu list .
 * Pokud je seznam list neaktivní nebo pokud je aktivní prvek
 * prvním prvkem seznamu, nic se neděje.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_DeleteBefore( DLList *list ) {
	if (list->activeElement) {
		// elem can't be first
		if (list->activeElement->previousElement) {
            DLLElementPtr tmpPtr = list->activeElement->previousElement;
            list->activeElement->previousElement = tmpPtr->previousElement;
			if (tmpPtr == list->firstElement) { // 2nd elem in list
				list->firstElement = list->activeElement;
			} else { // some in middle or end
			    tmpPtr->previousElement->nextElement = list->activeElement;
			}
            free(tmpPtr);
			tmpPtr = NULL;
		}
	}
}

/**
 * Vloží prvek za aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu za právě aktivní prvek
 */
void DLL_InsertAfter( DLList *list, int data ) {
	// need to know where insert elem
	if (list->activeElement) {
		// alloc
		DLLElementPtr MyDLLElementPtr = (DLLElementPtr)malloc(sizeof(struct DLLElement));
		if (!MyDLLElementPtr) {
			DLL_Error();
			return;
		}

		// init newElem
		MyDLLElementPtr->data = data;
		MyDLLElementPtr->previousElement = list->activeElement;
		MyDLLElementPtr->nextElement 	 = list->activeElement->nextElement;

		// handle when activeElem is lastElem
		if (list->activeElement == list->lastElement) {
			list->lastElement = MyDLLElementPtr;
		} else { // or if activeElem is not lastElem
			list->activeElement->nextElement->previousElement = MyDLLElementPtr;
		}

		list->activeElement->nextElement = MyDLLElementPtr;
	}
}

/**
 * Vloží prvek před aktivní prvek seznamu list.
 * Pokud nebyl seznam list aktivní, nic se neděje.
 * V případě, že není dostatek paměti pro nový prvek při operaci malloc,
 * volá funkci DLL_Error().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Hodnota k vložení do seznamu před právě aktivní prvek
 */
void DLL_InsertBefore( DLList *list, int data ) {
	// need to know where inser Elem
	if (list->activeElement) {
		// aloc mem
		DLLElementPtr MyDLLElementPtr = (DLLElementPtr)malloc(sizeof(struct DLLElement));
		if (!MyDLLElementPtr) {
			DLL_Error();
			return;
		}

		// init newElem
		MyDLLElementPtr->data = data;
		MyDLLElementPtr->previousElement = list->activeElement->previousElement;
		MyDLLElementPtr->nextElement 	 = list->activeElement;

		// handle if activeElem is first
		if (list->activeElement == list->firstElement) {
			list->firstElement = MyDLLElementPtr;
		} else { // and of not firstElem
			list->activeElement->previousElement->nextElement = MyDLLElementPtr;
		}

		list->activeElement->previousElement = MyDLLElementPtr;
	}
}

/**
 * Prostřednictvím parametru dataPtr vrátí hodnotu aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, volá funkci DLL_Error ().
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param dataPtr Ukazatel na cílovou proměnnou
 */
void DLL_GetValue( DLList *list, int *dataPtr ) {
	if (list->activeElement) { // must have active list
		*dataPtr = list->activeElement->data;
	} else { // else error
		DLL_Error();
	}
}

/**
 * Přepíše obsah aktivního prvku seznamu list.
 * Pokud seznam list není aktivní, nedělá nic.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 * @param data Nová hodnota právě aktivního prvku
 */
void DLL_SetValue( DLList *list, int data ) {
	if (list->activeElement) { // need to know where data set
		list->activeElement->data = data;
	}
}

/**
 * Posune aktivitu na následující prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na posledním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Next( DLList *list ) {
	if (list->activeElement) {
		list->activeElement = list->activeElement->nextElement;
	}
}


/**
 * Posune aktivitu na předchozí prvek seznamu list.
 * Není-li seznam aktivní, nedělá nic.
 * Všimněte si, že při aktivitě na prvním prvku se seznam stane neaktivním.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 */
void DLL_Previous( DLList *list ) {
	if (list->activeElement) {
		list->activeElement = list->activeElement->previousElement;
	}
}

/**
 * Je-li seznam list aktivní, vrací nenulovou hodnotu, jinak vrací 0.
 * Funkci je vhodné implementovat jedním příkazem return.
 *
 * @param list Ukazatel na inicializovanou strukturu dvousměrně vázaného seznamu
 *
 * @returns Nenulovou hodnotu v případě aktivity prvku seznamu, jinak nulu
 */
int DLL_IsActive( DLList *list ) {
	return (list->activeElement != NULL);
}

/* Konec c206.c */
