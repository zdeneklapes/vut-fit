/**
 * error.c
 * Řešení IJC-DU1, příklad B), 7.3.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 */

#include "error.h"

void warning_msg(const char *fmt, ...)
{
	va_list pArgs;
	va_start(pArgs, fmt);
	va_arg(pArgs, char *);

	fprintf(stderr, "CHYBA: ");
	vfprintf(stderr, fmt, pArgs);

	va_end(pArgs);
}

void error_exit(const char *fmt, ...)
{
	va_list pArgs;
	va_start(pArgs, fmt);
	va_arg(pArgs, char *);

	fprintf(stderr, "CHYBA: ");
	vfprintf(stderr, fmt, pArgs);

	va_end(pArgs);

	exit(1);
}
