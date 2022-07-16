/******************************************************************************
 * sem.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file sem.h
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

#ifndef SEM_H
#define SEM_H

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include <sys/sem.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <errno.h>

#include "macros.h"
#include "error.h"
#include "struct_def_enum.h"

/******************************************************************************/
/***                               SEMAPHORES                               ***/
/******************************************************************************/
int semInit();
int semDestroy();

#endif //SEM_H

/*** End of file sem.h ***/

