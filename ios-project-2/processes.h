/******************************************************************************
 * processes.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file processes.h
 * @brief Create and Init processes
 * @author Zdenek Lapes <xlapes02>, FIT
 */

#ifndef PROCESSES_H
#define PROCESSES_H

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include <stdbool.h>
#include <unistd.h>

#include "struct_def_enum.h"
#include "macros.h"
#include "macros.h"
#include "error.h"

/******************************************************************************/
/***                                PROCESSES                               ***/
/******************************************************************************/
void createProcesses(args_t args, process_t *process);
process_t initProcess(void);

#endif // PROCESSES_H

/*** End of file processes.h ***/
