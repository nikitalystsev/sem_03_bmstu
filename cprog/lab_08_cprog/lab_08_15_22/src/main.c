#include "defines.h"
#include "matrix.h"
#include "revise.h"

int main(int argc, char const *argv[])
{
    int rc = 0;
    matrix_t matrix1, matrix2, matrix_res;

    INIT_MATRIX(matrix1);
    INIT_MATRIX(matrix2);
    INIT_MATRIX(matrix_res);

    if ((rc = check_args(argc, argv)) != 0)
        return rc;

    if (argc == 4)
    {
        if ((rc = read_matrix_from_file(&matrix_res, argv[2])) != 0)
            goto free;

        if ((rc = check_matrix_for_inverse(&matrix_res)) != 0)
            goto free;

        if ((rc = inversion_matrix(&matrix_res)) != 0)
            goto free;

        if ((rc = write_matrix_to_file_by_coord(&matrix_res, argv[3])) != 0)
            goto free;
        goto free;
    }
    else if (argc == 5)
    {
        if ((rc = read_matrix_from_file(&matrix1, argv[2])) != 0)
            goto free;

        if ((rc = read_matrix_from_file(&matrix2, argv[3])) != 0)
            goto free;

        if (strcmp(argv[1], "a") == 0)
        {
            if ((rc = check_matrix_for_add(&matrix1, &matrix2)) != 0)
                goto free;

            matrix_res.rows = matrix1.rows;
            matrix_res.cols = matrix1.cols;

            if ((rc = matrix_alloc(&matrix_res)) != 0)
                goto free;

            matrix_add(&matrix1, &matrix2, &matrix_res);
        }
        else if (strcmp(argv[1], "m") == 0)
        {
            if ((rc = check_matrix_for_mult(&matrix1, &matrix2)) != 0)
                goto free;

            matrix_res.rows = matrix1.rows;
            matrix_res.cols = matrix2.cols;

            if ((rc = matrix_alloc(&matrix_res)) != 0)
                goto free;

            matrix_mult(&matrix1, &matrix2, &matrix_res);
        }

        if ((rc = write_matrix_to_file_by_coord(&matrix_res, argv[4])) != 0)
            goto free;
        goto free;
    }

    free:
    {
        matrix_free(matrix_res.matrix, matrix_res.rows);
        matrix_free(matrix1.matrix, matrix1.rows);
        matrix_free(matrix2.matrix, matrix2.rows);
    }
    
    return rc;
}
