/******************************************************************************
 * helper.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file helper.h
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

#ifndef HELPER_H
#define HELPER_H

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "error.h"

/******************************************************************************/
/***                               HELPER FNS                               ***/
/******************************************************************************/
int toInt(char *string);
int randomNum(void);

#endif // HELPER_H
