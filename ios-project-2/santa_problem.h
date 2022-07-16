/******************************************************************************
 * santa_problem.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file santa_problem.h
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

#ifndef SANTA_PROBLEM_H
#define SANTA_PROBLEM_H

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "stdio.h"
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include "struct_def_enum.h"
#include "helper.h"
#include "macros.h"

/******************************************************************************/
/***                               GLOBAL VARS                              ***/
/******************************************************************************/
extern struct sembuf sem_buf_u1;
extern struct sembuf sem_buf_u3;
extern struct sembuf sem_buf_s1;
extern union semun semun_info;

/******************************************************************************/
/***                              SANTA PROBLEM                             ***/
/******************************************************************************/
void santaJob(args_t args);
void reindeerJob(process_t process, args_t args);
void elfJob(process_t process, args_t args);
void getHelp(process_t process);
void elfHoliday(process_t process);
void helpElves(void);
void getHitched(process_t process);

#endif //SANTA_PROBLEM_H

/*** End of file santa_problem.h ***/
