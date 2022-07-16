##
# The Eight Queens Problem (SAT solver)
# author Zdenek Lapes <xlapes02>
# date   2022-03-11

import argparse
import math
import numpy as np

######################################
# GLOBAL VARS
######################################
final_clauses = np.empty([1, 3], dtype=int)
final_clauses = np.delete(final_clauses, (0), axis=0)  # delete the unnecessary row
cnt_clauses = 0


######################################
# FUNCTIONS
######################################
def parse_args():
    parser = argparse.ArgumentParser(description=__file__)
    parser.add_argument(nargs='?', type=int, help="Size of chess table", dest='N')
    args = parser.parse_args()
    if args.N < 4:
        print("Argument must be equal or greate that 4")
        exit(1)
    return args


def create_chess_table_matrix(args):
    matrix = list()
    for idx in range(1, args.N ** 2 + 1):
        matrix.append(idx)
    return [matrix[idx:idx + args.N] for idx in range(0, len(matrix), args.N)]


def traverse_row(args, row):
    global cnt_clauses, final_clauses
    for idx in range(len(row)):
        for col in range(1, len(row)):
            if col + idx == len(row):
                break
            else:
                cnt_clauses += 1
                final_clauses = np.append(final_clauses, [[-row[idx], -row[idx + col], 0]], axis=0)


def traverse_rows(args, matrix):
    for idx in range(args.N):
        traverse_row(args, matrix[idx])  # for each row traverse it


def traverse_by_main_diagonal(args, matrix):
    global cnt_clauses
    for idx in range(args.N - 1):
        traverse_row(args, np.diag(matrix, idx))  # right
        if idx != 0:  # the main diagonal shouldn't be repeated twice
            traverse_row(args, np.diag(matrix, -idx))  # right down


def traverse_by_side_diagonal(args, matrix):
    global cnt_clauses
    for idx in range(args.N - 1):
        traverse_row(args, np.diag(np.fliplr(matrix), idx))  # left
        if idx != 0:  # the side diagonal shouldn't be repeated twice
            traverse_row(args, np.diag(np.fliplr(matrix), -idx))  # left down


def print_cnt(args):
    global final_clauses, cnt_clauses
    print(f"p cnf {args.N} {cnt_clauses}")
    for r in range(final_clauses.shape[0]):
        for c in range(final_clauses.shape[1]):
            print(final_clauses[r][c], end=" ")
        print()


def how_many_add(args):
    if args.N % 3 == 0:
        return 0
    elif args.N % 3 == 1:
        return 2
    elif args.N % 3 == 2:
        return 1


def one_queen_each_column(args, matrix):
    global final_clauses, cnt_clauses
    for idx_row, val_row in enumerate(matrix):
        for idx_col, val_col in enumerate(val_row):
            print(val_col, end=" ")
        cnt_clauses += 1
        print(0)


def main():
    global final_clauses
    args = parse_args()
    matrix = create_chess_table_matrix(args)
    traverse_rows(args, np.array(matrix))  # rows can't be two queens
    traverse_rows(args, np.transpose(np.array(matrix, dtype=int)))  # cols can't be two queens
    traverse_by_main_diagonal(args,  np.array(matrix, dtype=int))  # all diagonals left-up to right-bottom can't be 2 queens
    traverse_by_side_diagonal(args,  np.array(matrix, dtype=int))  # all diagonals right-up to left-bottom can't be 2 queens
    print_cnt(args)
    one_queen_each_column(args, np.array(matrix, dtype=int))  # there is at least oen queen in each column


if __name__ == '__main__':
    main()
