/**
 * io.c
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "io.h"

int read_word(char *s, int max, FILE *f)
{
	for (int i = 0, c; (c = fgetc(f)) != EOF || i > 1; i++)
	{
//	    because can be more spaces between each words
	    if (isspace(c) && i == 0)
        {
	        while (isspace(c = fgetc(f)))
                ;
        }

		// if to long go to first space and return
		if (i == max)
		{
            while (true)
            {
                if ((c = fgetc(f)) == EOF || isspace(c))
                {
                    return i;
                }
            }
        }
		// is space end of word return length; isspace() - return 0 if false ; must have also conditional fro EOF,
		// because it handle if the file in not ended by '\n'
		else if (isspace(c) || (c == EOF && i > 0))
		{
//		    s[i+1] from calloc have already '\0'
		    return i;
        }
//      end file --> return EOF
		else if(c == EOF)
        {
            return EOF;
        }
		// save char
		else
        {
            s[i] = (char)c;
        }
	}
//  end file --> return EOF
	return EOF;
}
