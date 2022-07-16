/******************************************************************************
 * macros.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file macros.h
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

#ifndef MACROS_H
#define MACROS_H

#include <stdio.h>
#include <sys/sem.h>

#include "struct_def_enum.h"

/******************************************************************************/
/***                               GLOBAL VARS                              ***/
/******************************************************************************/
shm_t *shm;
FILE *f;

/******************************************************************************/
/***                                 MSG                                 ***/
/******************************************************************************/
#define SANTA_SLEEP_MSG             "%d: Santa: going to sleep\n"
#define SANTA_HELP_MSG              "%d: Santa: helping elves\n"
#define SANTA_CLOSE_SHOP_MSG        "%d: Santa: closing workshop\n"
#define SANTA_CHRISTMAS_STARTED_MSG "%d: Santa: Christmas started\n"
#define ELF_START_MSG               "%d: Elf %d: started\n"
#define ELF_NEED_HELP_MSG           "%d: Elf %d: need help\n"
#define ELF_GET_HELP_MSG            "%d: Elf %d: get help\n"
#define ELF_CLOSED_MSG              "%d: Elf %d: taking holidays\n"
#define RD_START_MSG                "%d: RD %d: rstarted\n"
#define RD_RETURN_MSG               "%d: RD %d: return home\n"
#define RD_HITCHED_MSG              "%d: RD %d: get hitched\n"

/******************************************************************************/
/***                               INIT VALUES                              ***/
/******************************************************************************/
#define INCREASE(x)     ( (x) = (x) + 1 )
#define INIT_VALUE_0    ( 0 )
#define INIT_VALUE_U1   ( 1 )
#define INIT_VALUE_S1   ( -1 )
#define MAX(a, b)       ( ((a) < (b)) ? (b) : (a) )

/******************************************************************************/
/***                                 LIMITS                                 ***/
/******************************************************************************/
#define MAX_LIMIT       1000    // max elf, and time for usleep
#define MAX_REIN_LIMIT  20      // max reindeers
#define MIN_LIMIT       0       // min for all vars in args_t

/******************************************************************************/
/***                               SLEEP TIME                               ***/
/******************************************************************************/
#define REINDEER_SLEEP  ((randomNum() % (args.TR/2+1)) + (args.TR/2))
#define ELF_SLEEP       ((randomNum()) % (args.TE+1))
#define SANTA_SLEEP     ((randomNum()) % (1000))


/******************************************************************************/
/***                              ERROR CODES                               ***/
/******************************************************************************/
#define EINVAL                  22  // Invalid argument
#define ERR_CODE                2   // err
#define ERR_CODE_SHM            3   // err + shmInit failed
#define ERR_CODE_SHM_SEM        4   // err + shmInit + semInit failed
#define ERR_CODE_SHM_SEM_FORK   5   // err + shmInit + semInit + fork failed

/******************************************************************************/
/***                             DEBUG VARS                                 ***/
/******************************************************************************/
#define DEBUG       0   // DEBUG_PRINT
#define DEBUG_LITE  0   // DEBUG_PRINT_LITE
#define DEBUG_VALUE 0   // SEM_GETVALUE
#define ACTION      1   // PRINT_ACTION

/******************************************************************************/
/***                           DEBUG REPORTS                                ***/
/******************************************************************************/
#define DEBUG_PRINT_LITE(fmt, ...) \
            do { if (DEBUG_LITE) fprintf(stderr, fmt, __VA_ARGS__); } while (0)
#define DEBUG_PRINT(fmt, ...) \
        do { if (DEBUG) fprintf(stderr, "%s:%d:%s(): " fmt, __FILE__, \
                                __LINE__, __func__, __VA_ARGS__); } while (0)
#define SEM_GETVALUE(semName, semNum, operation, semun_info)   do {                                    \
                                if (DEBUG_VALUE) {                   \
                                int val = semctl(semName, semNum, operation, semun_info); \
                                fprintf(stderr, "\t"#semName": %d\n", val); }   \
                                } while (0)
#define PRINT_ACTION(fmt, ...) \
            do { if (ACTION) { \
                    semop(shm->printSem, &sem_buf_s1, 1); \
                    fprintf(f, fmt, __VA_ARGS__); \
                    semop(shm->printSem, &sem_buf_u1, 1); \
                }                   \
            } while (0)

/******************************************************************************/
/***                                FILENAME                                ***/
/******************************************************************************/
#define OUTPUT_FILENAME "proj2.out"

/******************************************************************************/
/***                                 PRINT                                  ***/
/******************************************************************************/
#define BOLD    "\033[1m"   // print bold text
#define NORMAL  "\033[0m"   // print normal text
#define RED     "\033[31m"  // print red text

#endif // MACROS_H
