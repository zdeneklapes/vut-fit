/**
 * error.h
 * Řešení IJC-DU1, příklad B), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void warning_msg(const char *fmt, ...);
void error_exit(const char *fmt, ...);

#endif // ERROR_H
