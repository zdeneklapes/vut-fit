/******************************************************************************
 * processes.c
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file processes.c
 * @brief Create and Init processes
 * @author Zdenek Lapes <xlapes02>, FIT
 */


/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "processes.h"

/******************************************************************************/
/***                                PROCESSES                               ***/
/******************************************************************************/
#if 1
void createProcesses(args_t args, process_t *process) {
    int retVal;
    for (int i = 0; i < MAX(args.NE, args.NR) && shm->forkFailed == false; i++) {
//      ELVES
        if (i < args.NE) {
            if ((retVal = fork()) == 0) { // child ==> break
                process->procName = ELF_PROCESS;
                process->procID = i + 1;
                return;
            } else if (retVal < 0) {
                // err = proccess haven't been created
                shm->forkFailed = true;
            }
        }

//      REINDEERS
        if (i < args.NR) {
            if ((retVal = fork()) == 0) { // child ==> break
                process->procName = REINDER_PROCESS;
                process->procID = i + 1;
                return;
            } else if (retVal < 0) {
                // err = proccess haven't been created
                shm->forkFailed = true;
            }
        }

//      SANTA
        if (i == 0) {
            if ((retVal = fork()) == 0) { // child ==> break
                process->procName = SANTA_PROCESS;
                return;
            } else if (retVal < 0) {
                // err = proccess haven't been created
                shm->forkFailed = true;
            }
        }
    }
//  let go all processes here because then can main process go to error_exit() or return
    short semopNum = args.NE + args.NR + 2; // + 2 Santa+Main
    struct sembuf sem_buf_X = {.sem_num = 0, .sem_op = semopNum, .sem_flg = 0};
    semop(shm->forkErrorSem, &sem_buf_X, 1);

    //      MAIN PROCESS
    if (shm->forkFailed == true) {
        error_exit(7, "Fork failed: ", process);
    }
}

process_t initProcess(void) {
    process_t proc = {.procName = MAIN_PROCESS,
            .procID = 0};
    return proc;
}
#endif

/*** End of file processes.c ***/
