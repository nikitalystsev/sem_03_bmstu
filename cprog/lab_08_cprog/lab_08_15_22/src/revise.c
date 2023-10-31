#include "revise.h"

int check_args(int argc, char const *argv[])
{
    if (argc != 5 && argc != 4)
        return ERR_COUNT_ARGS;
    else if (argc == 5 && strcmp(argv[1], "a") != 0 && strcmp(argv[1], "m") != 0)
        return ERR_COUNT_ARGS;
    else if (argc == 4 && strcmp(argv[1], "o") != 0)
        return ERR_COUNT_ARGS;

    return EXIT_SUCCESS;
}

int check_index(int *const index, const int size, FILE *file)
{
    if (fscanf(file, "%d", index) != 1)
        return ERR_INDEX_READ;

    if (*index <= 0 || *index > size)
        return ERR_INDEX;

    return EXIT_SUCCESS;
}

int check_matrix_for_inverse(const matrix_t *const matrix)
{
    if (matrix->rows != matrix->cols)
        return ERR_INV_SIZE;

    double det;
    if (gauss_det(matrix, &det) != 0)
        return ERR_ALLOC_MATRIX;

    if (fabs(det) < EPS || isnan(det))
        return ERR_DET;

    return EXIT_SUCCESS;
}

int check_matrix_for_add(const matrix_t *const matrix1,
const matrix_t *const matrix2)
{
    if (matrix1->rows != matrix2->rows || matrix1->cols != matrix2->cols)
    {
        return ERR_ADD_OPER;
    }
    
    return EXIT_SUCCESS;
}

int check_matrix_for_mult(const matrix_t *const matrix1,
const matrix_t *const matrix2)
{
    if (matrix1->cols != matrix2->rows)
    {
        return ERR_MULT_OPER;
    }
    
    return EXIT_SUCCESS;
}
