#ifndef __READ_H__
#define __READ_H__

#include "defines.h"
#include "linked_list_operations.h"

int get_choise_option_of_mtr_create(int *const choise_option);

int get_size_matrix(int *const row, int *const col);

int get_size_vector_col(int *const row);

int check_sizes_for_mult(const int col_matrix, const int row_vector_col);

int input_no_zero_elem(int *const count_no_zero, const int row, const int col);

void fill_std_matrix_by_random(std_matrix_t *const std_matrix,
                               const int count_no_zero);

int get_count_no_zero(std_matrix_t *const std_matrix);

int read_indexes_std_matrix_for_elem(int *const ind_row,
                                     int *const ind_col,
                                     const int count_row,
                                     const int count_col);

int get_matrix_element(int *const value);

int fill_matrix_by_input(std_matrix_t *const std_matrix,
                         const int count_no_zero);


void init_std_matrix_by_zero(std_matrix_t *const std_matrix);

int array_alloc(int **array,
                int count_elements);

int matrix_alloc(std_matrix_t *const matrix);

void matrix_free(int **matrix, const size_t n);

int get_size_std_matrix_from_file(std_matrix_t *const std_matrix, FILE *file);

int get_std_matrix_from_file(std_matrix_t *const std_matrix,
                             const char *const file_name);

int copy_std_matrix_to_sparse_matrix(const std_matrix_t *const std_matrix,
                                     sparse_matrix_t *const sparse_matrix,
                                     const int count_no_zero);

#endif
