#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "defines.h"

typedef struct
{
    double **matrix;
    size_t rows;
    size_t cols;
} matrix_t;

#define INIT_MATRIX(matrix_1)   \
    do                          \
    {                           \
        matrix_1.matrix = NULL; \
        matrix_1.rows = 0;      \
    } while (0);

int get_matrix_size(int *const n, int *const m, FILE *file);

int read_matrix_from_file(matrix_t *const matrix, const char *const file_name);

int matrix_alloc(matrix_t *const matrix);

void matrix_free(double **data, const size_t n);

int gauss_det(const matrix_t *const matrix_cp, double *const det);

int inversion_matrix(matrix_t *const matrix);

void matrix_add(matrix_t *const matrix1,
matrix_t *const matrix2,
matrix_t *const matrix_res);

void matrix_mult(matrix_t *const matrix1,
matrix_t *const matrix2,
matrix_t *const matrix_res);

int get_count_no_zero(const matrix_t *const matrix);

int write_matrix_to_file_by_coord(const matrix_t *const matrix,
const char *const file_name);

#endif
