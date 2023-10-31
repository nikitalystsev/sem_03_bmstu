#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

#define MAX_SIZE_MATRIX 20000
#define MAX_PRINT_MATIRX 225
#define MAX_PRINT_VECTOR 20

#define FILE1 "./data/test4_mtr_55.txt"
#define FILE2 "./data/test4_mtr_51.txt"

#define ERR_READ_IND_ROW 100
#define ERR_IND_ROW 101
#define ERR_READ_IND_COL 102
#define ERR_IND_COL 103
#define ERR_READ_VALUE 104
#define ERR_ALREADY_NO_ZERO 105
#define ERR_READ_COUNT_ROW 106
#define ERR_COUNT_ROW 107
#define ERR_COUNT_COL 108
#define ERR_READ_COUNT_NO_ZERO 109
#define ERR_COUNT_NO_ZERO 110
#define ERR_ALLOC_MEMORY 111
#define ERR_ALLOC_MATRIX 112
#define ERR_OPEN_FILE 113
#define ERR_READ_CHOISE_OPTION 114
#define ERR_CHOISE_OPTION 115
#define ERR_CHECK_SIZES 116
#define ERR_VALUE 117
// вектор-столбец как матрица
typedef struct 
{
    int **matrix;
    int count_row;
    int count_col;
} std_matrix_t;


typedef struct s_list
{
    int index_start_row;
    struct s_list *next_elem;
} list_t;

typedef struct 
{
    int count_row;
    int count_col;
    int count_no_zero;

    int *A;
    int *JA;
    list_t IA;
} sparse_matrix_t;

#endif
