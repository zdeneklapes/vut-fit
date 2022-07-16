/******************************************************************************
 * struct_def_enum.h
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file struct_def_enum.h
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */


#ifndef STRUCT_DEF_ENUM_H
#define STRUCT_DEF_ENUM_H

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include <stdbool.h>

/******************************************************************************/
/***                          ENUM, STRUCTS, TYPEDEFS                       ***/
/******************************************************************************/
typedef struct args_s {
    int NE; // elfs
    int NR; // reindeers
    int TE; // max time to elf work i milisec
    int TR; // max time to reindeer return home in milisec
} args_t;

typedef struct process_s {
    int procName; // process name
    int procID; // process id
} process_t;

typedef struct shm_s {
//    CNT
    int elves; // counter of elves
    int reindeer; // counetr of reindeers
    int actID; // print id
    int shmID; // shm id
    bool forkFailed; // because in processes need to know all processes this value
    bool closedShop; // when elf should go to holiday
//    SEM
    int elfSem;
    int reindeerSem;
    int santaSem;
    int mutexSem;
    int printSem;
    int elfMutex;
    int reindeerMutex;
    int santaMutex;
    int forkErrorSem;
} shm_t;

// because on macos(big sur) it runs without this, on merlin it doesn't
#ifdef __unix__
union semun {
int val; /* value for SETVAL */
struct semid_ds *buf; /* buffer for IPC_STAT, IPC_SET */
unsigned short int *array; /* array for GETALL, SETALL */
struct seminfo *__buf; /* buffer for IPC_INFO */
};
#endif

enum process_e {MAIN_PROCESS, SANTA_PROCESS, REINDER_PROCESS, ELF_PROCESS};

#endif // STRUCT_DEF_ENUM_H
