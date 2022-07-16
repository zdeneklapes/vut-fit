/******************************************************************************
 * helper.c
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file helper.c
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "helper.h"

/******************************************************************************/
/***                               HELPER FNS                               ***/
/******************************************************************************/
int toInt(char *string) {
    errno = 0;
    char *endPtr = NULL;
    long int number = strtol(string, &endPtr, 10);
    //    if negative num or not a num ==> exit
    if (errno != 0 || number < 0 || strcmp(endPtr, "") != 0) { error_exit(EINVAL, "Wrong arguments - not a number or negative number. Please look at the usage!", NULL); }
    return (int)number;
}

int randomNum(void) {
    srand(time(NULL));
    return rand();
}
