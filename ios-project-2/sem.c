/******************************************************************************
 * sem.c
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file sem.c
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "sem.h"

/******************************************************************************/
/***                                SEMAPHORES                              ***/
/******************************************************************************/
int semInit() {
    shm->elfSem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    shm->reindeerSem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    shm->santaSem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    shm->mutexSem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    shm->printSem = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    shm->elfMutex = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    shm->reindeerMutex = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    shm->santaMutex = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);
    shm->forkErrorSem= semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0666);

    if (shm->elfSem == INIT_VALUE_S1 || semctl(shm->elfSem, 0, SETVAL, INIT_VALUE_U1) == -1) { error_exit(6, "Create SEM failed: ", NULL); }
    if (shm->reindeerSem == INIT_VALUE_S1 || semctl(shm->reindeerSem, 0, SETVAL, INIT_VALUE_0) == -1) { error_exit(6, "Create SEM failed: ", NULL);; }
    if (shm->santaSem == INIT_VALUE_S1 || semctl(shm->santaSem, 0, SETVAL, INIT_VALUE_0) == -1) { error_exit(6, "Create SEM failed: ", NULL); }
    if (shm->mutexSem == INIT_VALUE_S1 || semctl(shm->mutexSem, 0, SETVAL, INIT_VALUE_0) == -1) { error_exit(6, "Create SEM failed: ", NULL); }
    if (shm->printSem == INIT_VALUE_S1 || semctl(shm->printSem, 0, SETVAL, INIT_VALUE_U1) == -1) { error_exit(6, "Create SEM failed: ", NULL); }
    if (shm->elfMutex == INIT_VALUE_S1 || semctl(shm->elfMutex, 0, SETVAL, INIT_VALUE_U1) == -1) { error_exit(6, "Create SEM failed: ", NULL); }
    if (shm->reindeerMutex == INIT_VALUE_S1 || semctl(shm->reindeerMutex, 0, SETVAL, INIT_VALUE_U1) == -1) { error_exit(6, "Create SEM failed: ", NULL); }
    if (shm->santaMutex == INIT_VALUE_S1 || semctl(shm->santaMutex, 0, SETVAL, INIT_VALUE_U1) == -1) { error_exit(6, "Create SEM failed: ", NULL); }
    if (shm->forkErrorSem == INIT_VALUE_S1 || semctl(shm->forkErrorSem, 0, SETVAL, INIT_VALUE_0) == -1) { error_exit(6, "Create SEM failed: ", NULL); }

    return 1;
}

int semDestroy() {
    bool err = false;
    if ((shm->elfSem != INIT_VALUE_S1) && (semctl(shm->elfSem, 0, IPC_RMID) == -1)) { err = true; }
    if ((shm->reindeerSem != INIT_VALUE_S1) && (semctl(shm->reindeerSem, 0, IPC_RMID) == -1)) { err = true; }
    if ((shm->santaSem != INIT_VALUE_S1) && (semctl(shm->santaSem, 0, IPC_RMID) == -1)) { err = true; }
    if ((shm->mutexSem != INIT_VALUE_S1) && (semctl(shm->mutexSem, 0, IPC_RMID) == -1)) { err = true; }
    if ((shm->printSem != INIT_VALUE_S1) && (semctl(shm->printSem, 0, IPC_RMID) == -1)) { err = true; }
    if ((shm->elfMutex != INIT_VALUE_S1) && (semctl(shm->elfMutex, 0, IPC_RMID) == -1)) { err = true; }
    if ((shm->reindeerMutex != INIT_VALUE_S1) && (semctl(shm->reindeerMutex, 0, IPC_RMID) == -1)) { err = true; }
    if ((shm->santaMutex != INIT_VALUE_S1) && (semctl(shm->santaMutex, 0, IPC_RMID) == -1)) { err = true; }
    if ((shm->forkErrorSem != INIT_VALUE_S1) && (semctl(shm->forkErrorSem, 0, IPC_RMID) == -1)) { err = true; }
    return (err == false) ? (1) : (errno);
}

/*** End of file sem.c ***/
