/**
 * io.h
 * Řešení IJC-DU2, příklad 2), 15.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int read_word(char *s, int max, FILE *f);

#endif // IO_H
