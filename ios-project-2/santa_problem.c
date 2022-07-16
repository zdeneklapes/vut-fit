/******************************************************************************
 * santa_problem.c
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file santa_problem.c
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */


/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "santa_problem.h"

/******************************************************************************/
/***                               GLOBAL VARS                              ***/
/******************************************************************************/
struct sembuf sem_buf_u1 = {.sem_num = 0, .sem_op = 1, .sem_flg = 0};
struct sembuf sem_buf_u3 = {.sem_num = 0, .sem_op = 3, .sem_flg = 0};
struct sembuf sem_buf_s1 = {.sem_num = 0, .sem_op = -1, .sem_flg = 0};
union semun semun_info = {.val = 0};

/******************************************************************************/
/***                              SANTA PROBLEM                             ***/
/******************************************************************************/
void santaJob(args_t args) {
    while (1) {
//      every time when help elves go to sleep
        PRINT_ACTION(SANTA_SLEEP_MSG, INCREASE(shm->actID));
        usleep(SANTA_SLEEP);

        semop(shm->santaSem, &sem_buf_s1, 1); // can be waiked up by reindeer or elf to help
        semop(shm->santaMutex, &sem_buf_s1, 1); //
        if (shm->reindeer >= args.NR) { // if the last reindeer then cristmas started and shop get close
            PRINT_ACTION(SANTA_CLOSE_SHOP_MSG, INCREASE(shm->actID));

            semop(shm->reindeerSem, &sem_buf_u1, 1); // reindeer will go one by one, then let go santa close shop

            semop(shm->santaMutex, &sem_buf_s1, 1); // wait until all reindeer getHithced
            PRINT_ACTION(SANTA_CHRISTMAS_STARTED_MSG, INCREASE(shm->actID));

            shm->closedShop = true; // then closed shop and start Christmas
            struct sembuf sem_buf_NE = {.sem_num = 0, .sem_op = (short)args.NE, .sem_flg = 0};
            semop(shm->mutexSem, &sem_buf_NE, 1);
            semop(shm->elfSem, &sem_buf_NE, 1);
            semop(shm->elfMutex, &sem_buf_NE, 1);
            exit(0);
        } else if (shm->elves == 3) {
            helpElves();
        }
        semop(shm->santaMutex, &sem_buf_u1, 1); // make it free for next loop
    }
}

void reindeerJob(process_t process, args_t args) {
    PRINT_ACTION(RD_START_MSG, INCREASE(shm->actID), process.procID);
    usleep(REINDEER_SLEEP); // interval <TR/2,TR>

    semop(shm->reindeerMutex, &sem_buf_s1, 1); // one by one reindeer
    PRINT_ACTION(RD_RETURN_MSG, INCREASE(shm->actID), process.procID);

    shm->reindeer++; // increment returning reindeer counter
    if (shm->reindeer == args.NR) {
        semop(shm->santaSem, &sem_buf_u1, 1); // if last reindeer return let go santa
    }
    semop(shm->reindeerMutex, &sem_buf_u1, 1); // let go next reindeer

    getHitched(process);
    exit(0);
}

void elfJob(process_t process, args_t args) {
    PRINT_ACTION(ELF_START_MSG, INCREASE(shm->actID), process.procID);
    while (1) {
        usleep(ELF_SLEEP); // v intervalu <0,TE>

        // queue
        semop(shm->elfSem, &sem_buf_s1, 1); // elf queue
        semop(shm->elfMutex, &sem_buf_s1, 1); // one by one elf
        PRINT_ACTION(ELF_NEED_HELP_MSG, INCREASE(shm->actID), process.procID);
        if (shm->closedShop == true) {
            elfHoliday(process); break; // break is redundant I know it, but it is because clion warning
        } // if santa close shop then all elf need to take holidays

        shm->elves++; // counting elf in a queue
        if (shm->elves == 3) { // if more then three then Santa is waked up and helping elfes
            semop(shm->santaSem, &sem_buf_u1, 1); // is waked up
        } else {
            semop(shm->elfSem, &sem_buf_u1, 1); // next elf is let go
        }
        semop(shm->elfMutex, &sem_buf_u1, 1); // one by one elf let go

        getHelp(process); // elves get help from santa and continue to another cycle, until holiday
    }
}

void elfHoliday(process_t process) {
    PRINT_ACTION(ELF_CLOSED_MSG, INCREASE(shm->actID), process.procID);
    exit(0);
}

void getHelp(process_t process) {
    semop(shm->mutexSem, &sem_buf_s1, 1); // queue for decremented algorithm
    if ( shm->closedShop == true ) { // elf taking holidays
        elfHoliday(process);
    }
    PRINT_ACTION(ELF_GET_HELP_MSG, INCREASE(shm->actID), process.procID);
    shm->elves--; // decrement number of elf which need help
    if (shm->elves == 0) {
        semop(shm->elfSem, &sem_buf_u1, 1); // let go next 3 elf queue to help
        semop(shm->santaMutex, &sem_buf_u1, 1); // because santa need to wait until help all elves
    }
}

void helpElves(void) {
    PRINT_ACTION(SANTA_HELP_MSG, INCREASE(shm->actID));
    semop(shm->mutexSem, &sem_buf_u3, 1); // let go to decrement elf for help
    semop(shm->santaMutex, &sem_buf_s1, 1); // must help all elves and then go sleep
}

void getHitched(process_t process) {
    semop(shm->reindeerSem, &sem_buf_s1, 1); // getHitched when santa call preparedSleigh()
    PRINT_ACTION(RD_HITCHED_MSG, INCREASE(shm->actID), process.procID);
    shm->reindeer--;
    if (shm->reindeer == 0) {
        semop(shm->santaMutex, &sem_buf_u1, 1); // let go santa to start christmas
    }
    semop(shm->reindeerSem, &sem_buf_u1, 1); // let go one by one
}

/*** End of file santa_problem.c ***/
