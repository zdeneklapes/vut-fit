/******************************************************************************
 * arguments.c
 * Řešení IOS_PROJEKT 2, 29.4.2021
 * Autor: Zdenek Lapes <xlapes02>, FIT
 * Přeloženo: gcc 9.3.0
 *****************************************************************************/
/**
 * @file arguments.c
 * @brief
 * @author Zdenek Lapes <xlapes02>, FIT
 */


/******************************************************************************/
/***                                INCLUDES                                ***/
/******************************************************************************/
#include "arguments.h"

/******************************************************************************/
/***                                ARGUMENTS                               ***/
/******************************************************************************/
int readArgs(int argc, char **argv, args_t *args) {
//  CHECK IF ALL ARGS
    if (argc != 5) { error_exit(EINVAL, "Too few argument!", NULL); }

// check argument if is a positive number if does ==> save it to variables, otherwise ==> exit
    args->NE = toInt(argv[1]);
    args->NR = toInt(argv[2]);
    args->TE = toInt(argv[3]);
    args->TR = toInt(argv[4]);

//  check correctness of arguments
    if (!(args->NE > MIN_LIMIT && args->NE < MAX_LIMIT)) { error_exit(EINVAL, "Wrong arguments! ==> Mimo rozsah NE", NULL); }
    if (!(args->NR > MIN_LIMIT && args->NR < MAX_REIN_LIMIT)) { error_exit(EINVAL, "Wrong arguments! ==> Mimo rozsah NR", NULL); }
    if (!(args->TE >= MIN_LIMIT && args->TE <= MAX_LIMIT)) { error_exit(EINVAL, "Wrong arguments! ==> Mimo rozsah TE", NULL); }
    if (!(args->TR >= MIN_LIMIT && args->TR <= MAX_LIMIT)) { error_exit(EINVAL, "Wrong arguments! ==> Mimo rozsah TR", NULL); }

    return 1;
}

args_t initArgs(void) {
    args_t args = { .NE = 0,
            .NR = 0,
            .TE = 0,
            .TR = 0};
    return args;
}
