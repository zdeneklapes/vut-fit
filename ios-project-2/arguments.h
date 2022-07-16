/******************************************************************************
 * arguments.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file arguments.h
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

#ifndef ARGUMENTS_H
#define ARGUMENTS_H

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "macros.h"
#include "struct_def_enum.h"
#include "helper.h"
#include "error.h"

/******************************************************************************/
/***                                ARGUMENTS                               ***/
/******************************************************************************/
int readArgs(int argc, char **argv, args_t *args);
args_t initArgs(void);

#endif // ARGUMENTS_H
