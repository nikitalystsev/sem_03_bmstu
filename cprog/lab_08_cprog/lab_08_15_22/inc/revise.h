#ifndef __REVISE_H__
#define __REVISE_H__

#include "defines.h"

int check_args(int argc, char const *argv[]);

int check_index(int *const index, const int size, FILE *file);

int check_matrix_for_inverse(const matrix_t *const matrix);

int check_matrix_for_add(const matrix_t *const matrix1,
const matrix_t *const matrix2);

int check_matrix_for_mult(const matrix_t *const matrix1,
const matrix_t *const matrix2);

#endif
