/******************************************************************************
 * error.c
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file error.c
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */

/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "error.h"

/******************************************************************************/
/***                                  ERROR                                 ***/
/******************************************************************************/
void error_exit(const int code, const char *fmt, process_t *process)
{
    switch (code) {
        case 5: // err + rm SHM
            shmDestroy();
            perror(fmt);
            break;
        case 6: // err + rm SHM + rm SEM
            semDestroy();
            shmDestroy();
            perror(fmt);
            break;
        case 7: // err + rm SHM + rm SEM + rm fork
            if (process->procName == MAIN_PROCESS) {
                while(wait(NULL) > 0) {
                    ;
                }
                semDestroy();
                shmDestroy();
                perror(fmt);
            }
            break;
        default: // err args (EINVAL) |
            fprintf(stderr, RED "CHYBA: " NORMAL "%s\n", fmt);
            fprintf(stderr, BOLD "%s\n", "USAGE:");
            fprintf(stderr, NORMAL "%s\n", "./proj2 NE NR TE TR");
            fprintf(stderr, BOLD "%s\n", "Example: ");
            fprintf(stderr, NORMAL "%d\t%s\n", 1, "\t./proj2 5 4 100 100");
            fprintf(stderr, NORMAL "%d\t%s\n", 2, "MAX LIMITS:\t./proj2 999 19 1000 1000");
            fprintf(stderr, NORMAL "%d\t%s\n", 3, "MIN LIMITS:\t./proj2 1 1 0 0");
            break;
    }
    fclose(f);
    exit(code);
}

/*** End of file error.c ***/
