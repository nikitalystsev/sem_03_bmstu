#ifndef __MY_MATRIX_H__
#define __MY_MATRIX_H__

#include "defines.h"

typedef struct 
{
    int32_t **matrix;
    int row;
    int col;
} matrix_t;

int32_t **matrix_alloc(const int n, const int m);

void free_matrix(int32_t **matrix, const int n);

int read_size_matrix(int *const n, int *const m, FILE *const file);

int read_matrix_from_file(matrix_t *const matrix, FILE *const file);

void print_row(const int32_t *const row, const int m);

void print_matrix(const matrix_t *const matrix);

int write_matrix_to_file(const matrix_t *const matrix, 
const char *const file_name);

int delete_col(matrix_t *const matrix);

bool isnull(int32_t number);

int find_min_zero_matrix(matrix_t *const matrix);

#endif