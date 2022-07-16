/**
 * tail.c
 * Řešení IJC-DU2, příklad 1), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

/******************************************************************************/
/*** TODO ***/
/******************************************************************************/

/******************************************************************************/
/*** INCLUDE ***/
/******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

/******************************************************************************/
/*** MACRO ***/
/******************************************************************************/
#define CHAR_PRINT_LIMIT 511
#define ROW_PRINT_DEF 10
#define ALLOC_CHARS 520
#define ALLOC_ROWS 50

/******************************************************************************/
/*** STRUCT ***/
/******************************************************************************/
struct pole_s
{
	int fromRow;   // number from which row start printing if -1 not set value
	int countRows; // number of lines in file
	int numPrint;  // number lines to print
	int alocChars; // alokovano charu
	int alocRows;  // alokovano rows
	char *filename;
	char **rowsP;  // 2d pole
};

/******************************************************************************/
/*** TYPEDEF ***/
/******************************************************************************/
typedef unsigned long int ul;
typedef struct pole_s pole_t;

/******************************************************************************/
/*** ERROR ***/
/******************************************************************************/
#define BOLD "\033[1m"
#define NORMAL "\033[0m"
#define RED "\033[31m"
#define ERROR_ALLOC_CODE (-1)
#define OK_CODE (1)

void error_exit(const int code, const char *fmt)
{
	fprintf(stderr, RED "CHYBA: " NORMAL "%s\n", fmt);
	if (code == 2)
	{
        fprintf(stderr, BOLD "%s\n", "POUZITI:");
        fprintf(stderr, NORMAL "%s\n", "./tail [-n cislo] [soubor]");
        fprintf(stderr, BOLD "%s\n", "Priklady:");
        fprintf(stderr, NORMAL "%d\t%s\n", 1, "./tail soubor.txt");
        fprintf(stderr, NORMAL "%d\t%s\n", 2, "./tail -n +3 soubor.txt");
        fprintf(stderr, NORMAL "%d\t%s\n", 3, "./tail -n 3 <soubor.txt");
        fprintf(stderr, NORMAL "%d\t%s\n", 4, "cat soubor.txt | ./tail");
        fprintf(stderr, NORMAL "%d\t%s\n", 5, "cat soubor.txt | ./tail -n 3 soubor.txt");
        fprintf(stderr, NORMAL "%d\t%s\n", 6, "cat soubor.txt | ./tail -n +3 <soubor.txt");
    }
	exit(code);
}

/******************************************************************************/
/*** ALLOCATION ***/
/******************************************************************************/
void dealoc2D(pole_t *pole)
{
	int r = pole->alocRows;
//	dealloc every row
	for (int i = 0; i < r; i++)
	{
//	    ask for NULL if not is nothing to freed
	    if (pole->rowsP[i] != NULL)
        {
//	        reset row
	        memset(pole->rowsP[i], '\0', strlen(pole->rowsP[i]));
//	        free
            free(pole->rowsP[i]);
//          NULL because after free value is untouched
            pole->rowsP[i] = NULL;
        }
    }

//	dealloc pointer to rows; ask for NULL if not is nothing to freed
	if (pole->rowsP != NULL)
    {
//	    free
        free(pole->rowsP);
//      NULL because after free value is untouched
        pole->rowsP = NULL;
    }
}

int realloc2D(pole_t *pole)
{
	// realloc size
	int r = 2 * pole->alocRows, c = pole->alocChars;

	// reallocate old memory doubled sized memory
	char **newMem;
	if ((newMem = realloc(pole->rowsP, sizeof(pole->rowsP) * r)) == NULL)
	{
        return ERROR_ALLOC_CODE;
	}
	pole->rowsP = newMem;
	// allocate memory for every new alocated row
	for (int i = pole->alocRows; i < r; i++)
	{
		if ((pole->rowsP[i] = calloc(c, sizeof(char *))) == NULL)
        {
            return ERROR_ALLOC_CODE;
        }
	}
	// set new allocation size
	pole->alocRows = r;
    return OK_CODE;
}

int aloc2D(pole_t *pole)
{
	// alloc size
	int r = pole->alocRows, c = pole->alocChars;

	// alloc + check if NULL
    if ((pole->rowsP = calloc(r, sizeof(pole->rowsP))) == NULL)
    {
        return ERROR_ALLOC_CODE;
    }

	// every row
	for (int i = 0; i < r; i++)
	{
		if ((pole->rowsP[i] = calloc(c, sizeof(char *))) == NULL)
        {
            return ERROR_ALLOC_CODE;
        }
	}
    return OK_CODE;
}
/******************************************************************************/
/*** FUNCTIONS ***/
/******************************************************************************/
FILE *openFile(char *filename)
{
	// chech if file exist
	int result = access(filename, F_OK);
	if (result != 0)
    {
	    error_exit(2, "Spatne argumenty");
    }

	// open file and chech ok/err
	FILE *f = fopen(filename, "r");
	if (f == NULL)
	{
        error_exit(1, "Soubor se nepodarilo otevrit!");
    }

	return f;
}

ul toInt(char *length)
{
	char *endPtr;
	errno = 0;
	ul num = strtoul(length, &endPtr, 10);
	if (errno != 0 || strncmp(length, "-", 1) == 0)
	{
        error_exit(2, "Spatny argument --> neni cislo/zaporne cislo");
    }
	return num;
}

int countReadLines(FILE *f, pole_t *pole)
{
	int r = 0;				 // rows
	int c = pole->alocChars; // max chars to read
	for (; fgets(pole->rowsP[r], c, f) != NULL; r++)
	{
		if (r + 1 == pole->alocRows)
        {
		    if (realloc2D(pole) == -1)
            {
                return ERROR_ALLOC_CODE;
            }
        }
	}
	pole->countRows = r;
    return OK_CODE;
}

void printRows(pole_t *pole)
{
	size_t chars;
	int row;
    if (pole->fromRow > 0)
    {
//	    -1 to behave as like as posix tail;  print from specific number of line
        row = pole->fromRow - 1;
    }
//    for handle is someone will want to print more rows than file have  ==>  print all line
    else if (pole->numPrint >= pole->countRows)
    {
        row = 0;
    }
//    print only lst number of lines
    else
    {
        row = pole->countRows - pole->numPrint;
    }
	bool warning = false;
	for (; row < pole->countRows; row++)
	{
		chars = strlen(pole->rowsP[row]);
		char *rowP = pole->rowsP[row];
		if (chars > CHAR_PRINT_LIMIT && warning == false)
		{
			fprintf(stderr, "Byl prekrocen limit 511 znaku na radek! Pokracuje se v tisknu s maximalni delkou 511 znaku na radek.");
			warning = true;
			fprintf(stdout, "%.*s\n", CHAR_PRINT_LIMIT, rowP);
		}
		else if (chars > CHAR_PRINT_LIMIT && warning == true)
		{
			fprintf(stdout, "%.*s\n", CHAR_PRINT_LIMIT, rowP);
		}
		else
		{
			fprintf(stdout, "%.*s", CHAR_PRINT_LIMIT, rowP);
		}
	}
}

pole_t initPole()
{
	pole_t pole = {.fromRow = -1,
				   .numPrint = ROW_PRINT_DEF,
				   .filename = "",
				   .countRows = 0,
				   .alocChars = ALLOC_CHARS,
				   .alocRows = ALLOC_ROWS,
				   .rowsP = NULL};
	return pole;
}

void readArgs(int argc, char **argv, pole_t *pole)
{
//    it runs only if it has arguments
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-n") == 0)
        {
//          i++ go to next arg
            i++;
//            check if tail should print from a specific number of line or the last lines
            if (strncmp(argv[i], "+", 1) == 0)
            {
                pole->fromRow = toInt(argv[i]);
            }
            else
            {
                pole->numPrint = toInt(argv[i]);
            }
//          must be because next if consideer filename
            continue;
        }
//      save file name if it is not a stdin
        if (strncmp(argv[i], "<", 1) == 0)
        {
            break;
        }
        else
        {
            pole->filename = argv[i];
        }
    }
}

/******************************************************************************/
/*** MAIN ***/
/******************************************************************************/
int main(int argc, char *argv[])
{
    if (argc > 4)
    {
        error_exit(2, "Mnoho argumentu pro program");
    }
	// var
	FILE *f = stdin;
	pole_t pole = initPole();
	readArgs(argc, argv, &pole);
//	if the file is added ass argument, so I need to open it, because I cant read from stdin
    if (strcmp(pole.filename, "") != 0)
    {
        f = openFile(pole.filename);
    }
//  alocate memory
    if (aloc2D(&pole) == ERROR_ALLOC_CODE)
    {
        goto error1;
    }
//  read all file and store it in allocated memory + count lines
    if (countReadLines(f, &pole) == ERROR_ALLOC_CODE)
    {
        goto error1;
    }
//  print required lines
    printRows(&pole);
//  if is not a stdin then close file
    if (strcmp(pole.filename, "") != 0)
    {
        fclose(f);				  // close file
    }
    dealoc2D(&pole);
    return 0;

    error1:
        if (strcmp(pole.filename, "") != 0)
        {
            fclose(f);				  // close file
        }
        dealoc2D(&pole);
        return 1;
}

// debug - check corectness
//printf("%s\n", pole->filename);
//printf("%d\n", pole->numPrint);
//printf("%d\n", pole->fromRow);
//printf("%d\n", pole->alocChars);
//printf("%d\n", pole->alocRows);
//printf("%d\n", pole->countRows);
