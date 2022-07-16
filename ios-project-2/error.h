/******************************************************************************
 * error.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file error.h
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

#ifndef ERROR_H
#define ERROR_H

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>

#include "macros.h"
#include "sem.h"
#include "shm.h"


/******************************************************************************/
/***                                  ERROR                                 ***/
/******************************************************************************/
void error_exit(const int code, const char *fmt, process_t *process);

#endif // ERROR_H

/*** End of file error.h ***/
