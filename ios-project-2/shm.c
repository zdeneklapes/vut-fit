/******************************************************************************
 * shm.c
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file shm.c
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "shm.h"

/******************************************************************************/
/***                                   SHM                                  ***/
/******************************************************************************/
int shmInit() {
//  CREATE SHM
    int shmID = shmget(IPC_PRIVATE, sizeof(shm_t), IPC_CREAT | IPC_EXCL | 0666);
    if (shmID < 0) { error_exit(5, "Create SHM failed: ", NULL); }

//  GET PTR
    shm = shmat(shmID, NULL, 0);
    if (shm == (void *) -1) { error_exit(5, "Create SHM failed: ", NULL); }

//  INIT ALL STRUCT
//  CNT
    shm->elves = INIT_VALUE_0;
    shm->reindeer = INIT_VALUE_0;
    shm->actID = INIT_VALUE_0;
    shm->shmID = shmID;
    shm->forkFailed = false;
    shm->closedShop = false;
//  SEM
    shm->elfSem = INIT_VALUE_S1;
    shm->reindeerSem = INIT_VALUE_S1;
    shm->santaSem = INIT_VALUE_S1;

    shm->mutexSem = INIT_VALUE_S1;
    shm->printSem = INIT_VALUE_S1;

    shm->elfMutex = INIT_VALUE_S1;
    shm->reindeerMutex = INIT_VALUE_S1;
    shm->santaMutex = INIT_VALUE_S1;

    shm->forkErrorSem = INIT_VALUE_S1;

//  OK
    return 1;
}

int shmDestroy() {
//    destroy shm
    int shmID = shm->shmID;
    if (shmdt(shm) == -1) { return errno; }

//    removed shmID from used memory
    if (shmctl(shmID, IPC_RMID, NULL) == -1) { return errno; }

    return 1;
}

/*** End of file shm.c ***/
