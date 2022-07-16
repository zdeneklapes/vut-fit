
/* ******************************* c204.c *********************************** */
/*  Předmět: Algoritmy (IAL) - FIT VUT v Brně                                 */
/*  Úkol: c204 - Převod infixového výrazu na postfixový (s využitím c202)     */
/*  Referenční implementace: Petr Přikryl, listopad 1994                      */
/*  Přepis do jazyka C: Lukáš Maršík, prosinec 2012                           */
/*  Upravil: Kamil Jeřábek, září 2019                                         */
/*           Daniel Dolejška, září 2021                                       */
/* ************************************************************************** */
/*
** Implementujte proceduru pro převod infixového zápisu matematického výrazu
** do postfixového tvaru. Pro převod využijte zásobník (Stack), který byl
** implementován v rámci příkladu c202. Bez správného vyřešení příkladu c202
** se o řešení tohoto příkladu nepokoušejte.
**
** Implementujte následující funkci:
**
**    infix2postfix ... konverzní funkce pro převod infixového výrazu
**                      na postfixový
**
** Pro lepší přehlednost kódu implementujte následující pomocné funkce:
**    
**    untilLeftPar ... vyprázdnění zásobníku až po levou závorku
**    doOperation .... zpracování operátoru konvertovaného výrazu
**
** Své řešení účelně komentujte.
**
** Terminologická poznámka: Jazyk C nepoužívá pojem procedura.
** Proto zde používáme pojem funkce i pro operace, které by byly
** v algoritmickém jazyce Pascalovského typu implemenovány jako procedury
** (v jazyce C procedurám odpovídají funkce vracející typ void).
**
**/

// Vypracoval: Zdeněk Lapeš <xlapes02>

#include "c204.h"

int solved;

/**
 * Pomocná funkce untilLeftPar.
 * Slouží k vyprázdnění zásobníku až po levou závorku, přičemž levá závorka bude
 * také odstraněna.
 * Pokud je zásobník prázdný, provádění funkce se ukončí.
 *
 * Operátory odstraňované ze zásobníku postupně vkládejte do výstupního pole
 * znaků postfixExpression.
 * Délka převedeného výrazu a též ukazatel na první volné místo, na které se má
 * zapisovat, představuje parametr postfixExpressionLength.
 *
 * Aby se minimalizoval počet přístupů ke struktuře zásobníku, můžete zde
 * nadeklarovat a používat pomocnou proměnnou typu char.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void untilLeftPar( Stack *stack, char *postfixExpression, unsigned *postfixExpressionLength ) {
    char dataPtr;
    Stack_Top(stack, &dataPtr);
    Stack_Pop(stack);

    if (dataPtr != '(') {
        postfixExpression[*postfixExpressionLength] = dataPtr;
        *postfixExpressionLength += 1;

		// recurse - until I will get '('
        untilLeftPar(stack, postfixExpression, postfixExpressionLength);
    }
}

/**
 * Pomocná funkce doOperation.
 * Zpracuje operátor, který je předán parametrem c po načtení znaku ze
 * vstupního pole znaků.
 *
 * Dle priority předaného operátoru a případně priority operátoru na vrcholu
 * zásobníku rozhodneme o dalším postupu.
 * Délka převedeného výrazu a taktéž ukazatel na první volné místo, do kterého
 * se má zapisovat, představuje parametr postfixExpressionLength, výstupním
 * polem znaků je opět postfixExpression.
 *
 * @param stack Ukazatel na inicializovanou strukturu zásobníku
 * @param c Znak operátoru ve výrazu
 * @param postfixExpression Znakový řetězec obsahující výsledný postfixový výraz
 * @param postfixExpressionLength Ukazatel na aktuální délku výsledného postfixového výrazu
 */
void doOperation( Stack *stack, char c, char *postfixExpression, unsigned *postfixExpressionLength ) {
    char dataPtr;
    int isEmpty = Stack_IsEmpty(stack);

    switch (isEmpty) {
        case TRUE:
            Stack_Push(stack, c);
            break;
        case FALSE:
            Stack_Top(stack, &dataPtr);
            if (dataPtr == '(') {
                Stack_Push(stack, c);
            } else if ((dataPtr == '+' || dataPtr == '-') && (c == '*' || c == '/')) { // handling importance of operators
                Stack_Push(stack, c);
            } else if (dataPtr == '+' ||
                       dataPtr == '-' ||
                       dataPtr == '*' ||
                       dataPtr == '/') {
                postfixExpression[*postfixExpressionLength] = dataPtr; // save
                *postfixExpressionLength += 1;
                Stack_Pop(stack);

				// recurse - until I will can push c into stack
                doOperation(stack, c, postfixExpression, postfixExpressionLength);
            }
            break;
    }
}

/**
 * Konverzní funkce infix2postfix.
 * Čte infixový výraz ze vstupního řetězce infixExpression a generuje
 * odpovídající postfixový výraz do výstupního řetězce (postup převodu hledejte
 * v přednáškách nebo ve studijní opoře).
 * Paměť pro výstupní řetězec (o velikosti MAX_LEN) je třeba alokovat. Volající
 * funkce, tedy příjemce konvertovaného řetězce, zajistí korektní uvolnění zde
 * alokované paměti.
 *
 * Tvar výrazu:
 * 1. Výraz obsahuje operátory + - * / ve významu sčítání, odčítání,
 *    násobení a dělení. Sčítání má stejnou prioritu jako odčítání,
 *    násobení má stejnou prioritu jako dělení. Priorita násobení je
 *    větší než priorita sčítání. Všechny operátory jsou binární
 *    (neuvažujte unární mínus).
 *
 * 2. Hodnoty ve výrazu jsou reprezentovány jednoznakovými identifikátory
 *    a číslicemi - 0..9, a..z, A..Z (velikost písmen se rozlišuje).
 *
 * 3. Ve výrazu může být použit předem neurčený počet dvojic kulatých
 *    závorek. Uvažujte, že vstupní výraz je zapsán správně (neošetřujte
 *    chybné zadání výrazu).
 *
 * 4. Každý korektně zapsaný výraz (infixový i postfixový) musí být uzavřen
 *    ukončovacím znakem '='.
 *
 * 5. Při stejné prioritě operátorů se výraz vyhodnocuje zleva doprava.
 *
 * Poznámky k implementaci
 * -----------------------
 * Jako zásobník použijte zásobník znaků Stack implementovaný v příkladu c202.
 * Pro práci se zásobníkem pak používejte výhradně operace z jeho rozhraní.
 *
 * Při implementaci využijte pomocné funkce untilLeftPar a doOperation.
 *
 * Řetězcem (infixového a postfixového výrazu) je zde myšleno pole znaků typu
 * char, jenž je korektně ukončeno nulovým znakem dle zvyklostí jazyka C.
 *
 * Na vstupu očekávejte pouze korektně zapsané a ukončené výrazy. Jejich délka
 * nepřesáhne MAX_LEN-1 (MAX_LEN i s nulovým znakem) a tedy i výsledný výraz
 * by se měl vejít do alokovaného pole. Po alokaci dynamické paměti si vždycky
 * ověřte, že se alokace skutečně zdrařila. V případě chyby alokace vraťte namísto
 * řetězce konstantu NULL.
 *
 * @param infixExpression Znakový řetězec obsahující infixový výraz k převedení
 *
 * @returns Znakový řetězec obsahující výsledný postfixový výraz
 */
char *infix2postfix( const char *infixExpression ) {
    // alloc postfix string
	char *postfixExpressionPtr = (char *)malloc(MAX_LEN*sizeof(char));
	if (!postfixExpressionPtr) { // check if malloc was successful
		return NULL;
	}
	postfixExpressionPtr[MAX_LEN-1] = '\0'; // correctly ended string

	// alloc stack
	Stack *stack = (Stack *) malloc(sizeof(Stack));
	if (!stack) { // check if malloc was successful
		free(postfixExpressionPtr);
		return NULL;
	}
    Stack_Init(stack);

    unsigned int idx = 0; // idx for pos to write next char
	for (int i = 0; i < MAX_LEN-1; i++) {
	    char infixCurChar = infixExpression[i];

        if (infixExpression[i] == '\0') {
            break;
        } else if ((infixCurChar >= '0' && infixCurChar <= '9') ||
                   (infixCurChar >= 'a' && infixCurChar <= 'z') ||
                   (infixCurChar >= 'A' && infixCurChar <= 'Z')) {
			postfixExpressionPtr[idx] = infixCurChar;
			idx++;
		} else if (infixCurChar == '(') { // left bracket - push to stack
            Stack_Push(stack, infixCurChar);
		} else if (infixCurChar == '+' ||
                   infixCurChar == '-' ||
                   infixCurChar == '*' ||
                   infixCurChar == '/') {
            doOperation(stack, infixCurChar, postfixExpressionPtr, &idx);
		} else if (infixCurChar == ')') {
            untilLeftPar(stack, postfixExpressionPtr, &idx);
        } else if (infixCurChar == '=') {
            while(!Stack_IsEmpty(stack)) {
                char dataPtr = '\0';
                Stack_Top(stack, &dataPtr);
                Stack_Pop(stack);
                postfixExpressionPtr[idx] = dataPtr;
                idx++;
            }
		    postfixExpressionPtr[idx] = infixCurChar;
		    idx++;
		}
        if (idx < MAX_LEN) postfixExpressionPtr[idx] = '\0'; // set '\0' to have corrently ended string
	}
	free(stack);
	stack = NULL; // after free we get undefined value so set ptr to NULL
	return postfixExpressionPtr;
}

/* Konec c204.c */
