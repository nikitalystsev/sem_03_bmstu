#ifndef __PRINT_H__
#define __PRINT_H__

#include "defines.h"
#include "linked_list_operations.h"

void print_info(void);

void print_std_matrix(const std_matrix_t *const std_matrix);

void print_sparse_matrix(const sparse_matrix_t *const sparse_matrix);

void print_mult_result(const std_matrix_t *const std_vector_col_res,
                       const sparse_matrix_t *const sparse_vector_col_res);

void print_result(const std_matrix_t std_vector_col_res,
                  const sparse_matrix_t sparse_vector_col_res,
                  const long double std_mult_time,
                  const long double sparse_mult_time);

#endif
