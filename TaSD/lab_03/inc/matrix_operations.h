#ifndef __MATRIX_OPERATION_H__
#define __MATRIX_OPERATION_H__

#include "defines.h"
#include "read.h"

void std_matrix_mult(std_matrix_t *const std_matrix1,
                     std_matrix_t *const std_matrix2,
                     std_matrix_t *const std_matrix_res);

int transpose_vector_col(std_matrix_t *const std_matrix,
                         std_matrix_t *const std_transpose_matrix);

int get_data_by_pos(list_t *head, const int pos);

list_t *get_by_pos(list_t *head, const int pos);

void sparse_mult(sparse_matrix_t *const sparse_matrix1,
                 sparse_matrix_t *const sparse_vector,
                 sparse_matrix_t *const sparse_matrix_res);

#endif
