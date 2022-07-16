/******************************************************************************
 * proj2.c
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file proj2.c
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

/******************************************************************************/
/***                                TODO                                    ***/
/******************************************************************************/


/******************************************************************************/
/***                               INCLUDES                                 ***/
/******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "macros.h"
#include "struct_def_enum.h"
#include "arguments.h"
#include "processes.h"
#include "shm.h"
#include "sem.h"
#include "santa_problem.h"
#include "error.h"

/******************************************************************************/
/***                          FUNCTION DECLARATION                          ***/
/******************************************************************************/
void printProcesses(process_t process);

/******************************************************************************/
/***                                  MAIN                                  ***/
/******************************************************************************/
int main(int argc, char *argv[]) {
//  INIT ARGS to 0
    DEBUG_PRINT("Initializing arguments %c\n", ' ');
    args_t args = initArgs();

//  MAIN PROCESS
    DEBUG_PRINT("Initializing MAIN PROCESS %c\n", ' ');
    process_t process = initProcess();

//  READ and SET ARGS to arguments form command line
    DEBUG_PRINT("Setting arguments %c\n", ' ');
    readArgs(argc, argv, &args);

//  OPEN | CREATE file
    if ((f = fopen(OUTPUT_FILENAME, "w")) == NULL) {
        error_exit(1, "File can't be opened: ", NULL);
    }

//  SET BUFFER to NULL - can make problems when writing to it
    setbuf(f, NULL);

//  INIT Shared Memory
    DEBUG_PRINT("Init SHM %c\n", ' ');
    shmInit(shm); // errors are treated in fn

//  INIT Semaphore
    DEBUG_PRINT("Init SEM %c\n", ' ');
    semInit(shm); // errors are treated in fn

//  DEBUG Printing - can me turn_on/turn_off with macros from macros.h
    DEBUG_PRINT_LITE("args.NE: %d\n", args.NE);
    DEBUG_PRINT_LITE("args.NR: %d\n", args.NR);
    DEBUG_PRINT_LITE("args.TE: %d\n", args.TE);
    DEBUG_PRINT_LITE("args.TR: %d\n", args.TR);
    SEM_GETVALUE(shm->elfSem, 0, GETVAL, semun_info);
    SEM_GETVALUE(shm->reindeerSem, 0, GETVAL, semun_info);
    SEM_GETVALUE(shm->santaSem, 0, GETVAL, semun_info);
    SEM_GETVALUE(shm->mutexSem, 0, GETVAL, semun_info);
    SEM_GETVALUE(shm->printSem, 0, GETVAL, semun_info);
    SEM_GETVALUE(shm->elfMutex, 0, GETVAL, semun_info);
    SEM_GETVALUE(shm->reindeerMutex, 0, GETVAL, semun_info);
    SEM_GETVALUE(shm->santaMutex, 0, GETVAL, semun_info);
    SEM_GETVALUE(shm->forkErrorSem, 0, GETVAL, semun_info);
    DEBUG_PRINT_LITE("-----------------------------%c\n", '>');

//  CREATE PROCESSES
    DEBUG_PRINT("Creating processes %c\n", ' ');
    createProcesses(args, &process);
    semop(shm->forkErrorSem, &sem_buf_s1, 1);
    if (shm->forkFailed == true) {
        error_exit(7, "Fork failed: ", &process);
    }
    SEM_GETVALUE(shm->forkErrorSem, 0, GETVAL, semun_info);
//    printProcesses(process); // only debug print


#if 1
//  SANTA Problem
    if (process.procName == SANTA_PROCESS) {
        DEBUG_PRINT("Calling SantaJob %c\n", ' ');
        santaJob(args);
    }
    if (process.procName == REINDER_PROCESS) {
        DEBUG_PRINT("Calling ReindeerJob %c\n", ' ');
        reindeerJob(process, args);
    }
    if (process.procName == ELF_PROCESS) {
        DEBUG_PRINT("Calling ElfJob %c\n", ' ');
        elfJob(process, args);
    }
#endif


//  MAIN Processes wait until all his children exit
    while (wait(NULL) > 0) {
        ;
    }

//  ONLY MAIN Processes
    if (process.procName == MAIN_PROCESS) { DEBUG_PRINT_LITE("-----------------------------%c\n", '>'); }
    if (process.procName == MAIN_PROCESS) {
//      RM SEM - first because it is save in the SHM
        DEBUG_PRINT("Destroyed SEM %c\n", ' ');
        if (semDestroy(shm) != 1) { perror("Destroy SEM failed: "); }
//      RM SHM
        DEBUG_PRINT("Destroyed SHM %c\n", ' ');
        if (shmDestroy(shm) != 1) { perror("Destroyed SHM failed: "); }
    }
//  CLOSE FILE
    if (fclose(f) == EOF) {
        perror("File can't be closed: ");
    } else {
        DEBUG_PRINT("Closing file: %s", OUTPUT_FILENAME);
    }

    return 0;
}

void printProcesses(process_t process) {
    if (process.procName == ELF_PROCESS) { printf("ELF PID: \t%d\tID: %d\n", getpid(), process.procID); }
    if (process.procName == REINDER_PROCESS) { printf("REINDEERS PID: \t%d\tID: %d\n", getpid(), process.procID); }
    if (process.procName == SANTA_PROCESS) { printf("SANTA PID: \t%d\tID: %d\n", getpid(), process.procID); }
    if (process.procName == MAIN_PROCESS) { printf("MAIN PID: \t%d\tID: %d\n", getpid(), process.procID); }
}

/*** End of file proj2.c ***/
