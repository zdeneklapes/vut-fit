/******************************************************************************
 * shm.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file shm.h
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

#ifndef SHM_H
#define SHM_H

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <errno.h>

#include "macros.h"
#include "error.h"
#include "struct_def_enum.h"

/******************************************************************************/
/***                                   SHM                                  ***/
/******************************************************************************/
int shmInit();
int shmDestroy();

#endif // SHM_H
