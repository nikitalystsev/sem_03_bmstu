#include "defines.h"
#include "read.h"
#include "print.h"
#include "matrix_operations.h"
#include "timing.h"

int main(void)
{
    print_info();

    int rc = 0;

    int choise_option;

    if ((rc = get_choise_option_of_mtr_create(&choise_option)) != 0)
    {
        return rc;
    }

    int row, col, row_vector_col;
    if ((rc = get_size_matrix(&row, &col)) != 0)
    {
        return rc;
    }
    if ((rc = get_size_vector_col(&row_vector_col)) != 0)
    {
        return rc;
    }
    if ((rc = check_sizes_for_mult(col, row_vector_col)))
    {
        return rc;
    }

    std_matrix_t std_matrix, std_vector_col, std_vector_col_res, transp_vector_col;

    std_matrix.count_row = row;
    std_matrix.count_col = col;
    std_vector_col.count_row = row_vector_col;
    std_vector_col.count_col = 1;
    std_vector_col_res.count_row = row;
    std_vector_col_res.count_col = 1;

    sparse_matrix_t sparse_matrix, sparse_vector_col, sparse_vector_col_res, sparse_transp_vector_col;

    sparse_matrix.count_row = row;
    sparse_matrix.count_col = col;
    sparse_vector_col.count_row = row_vector_col;
    sparse_vector_col.count_col = 1;
    sparse_vector_col_res.count_row = row;
    sparse_vector_col_res.count_col = 1;

    sparse_transp_vector_col.count_row = 1;
    sparse_transp_vector_col.count_col = row_vector_col;

    int cnz_matrix, cnz_vector;
    printf("Введите количество ненулевых элементов в матрице (целое число от 0 до %d):\n", row * col);
    if ((rc = input_no_zero_elem(&cnz_matrix, row, col)) != 0)
    {
        return rc;
    }
    printf("Введите количество ненулевых элементов в векторе-столбце (целое число от 0 до %d):\n", row_vector_col);
    if ((rc = input_no_zero_elem(&cnz_vector, row_vector_col, 1)) != 0)
    {
        return rc;
    }
    sparse_matrix.count_no_zero = cnz_matrix;
    sparse_vector_col.count_no_zero = cnz_vector;

    // тут надо особождать еще при ошибке

    // выделяю память под стандартные матрицы
    if ((rc = matrix_alloc(&std_matrix)) != 0)
        return rc;
    if ((rc = matrix_alloc(&std_vector_col)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        return rc;
    }
    if ((rc = matrix_alloc(&std_vector_col_res)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        return rc;
    }

    // выделяю память под разреженные матрицы
    if ((rc = array_alloc(&sparse_matrix.A, cnz_matrix)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
        return rc;
    }
    if ((rc = array_alloc(&sparse_matrix.JA, cnz_matrix)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
        free(sparse_matrix.A);
        return rc;
    }
    if ((rc = array_alloc(&sparse_vector_col.A, cnz_vector)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
        free(sparse_matrix.A);
        free(sparse_matrix.JA);
        return rc;
    }
    if ((rc = array_alloc(&sparse_vector_col.JA, cnz_vector)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
        free(sparse_matrix.A);
        free(sparse_matrix.JA);
        free(sparse_vector_col.A);
        return rc;
    }
    if ((rc = array_alloc(&sparse_transp_vector_col.A, cnz_vector)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
        free(sparse_matrix.A);
        free(sparse_matrix.JA);
        free(sparse_vector_col.A);
        free(sparse_vector_col.JA);
        return rc;
    }
    if ((rc = array_alloc(&sparse_transp_vector_col.JA, cnz_vector)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
        free(sparse_matrix.A);
        free(sparse_matrix.JA);
        free(sparse_vector_col.A);
        free(sparse_vector_col.JA);
        free(sparse_transp_vector_col.A);
        return rc;
    }
    int cnz_res;
    switch (choise_option)
    {
    case 0:
        fill_std_matrix_by_random(&std_matrix, cnz_matrix);
        fill_std_matrix_by_random(&std_vector_col, cnz_vector);
        break;
    case 1:
        printf("\nВвод значений ненулевых элементов матрицы\n");
        if ((rc = fill_matrix_by_input(&std_matrix, cnz_matrix)) != 0)
        {
            matrix_free(std_matrix.matrix, std_matrix.count_row);
            matrix_free(std_vector_col.matrix, std_vector_col.count_row);
            matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
            free(sparse_matrix.A);
            free(sparse_matrix.JA);
            free(sparse_vector_col.A);
            free(sparse_vector_col.JA);
            free(sparse_transp_vector_col.A);
            free(sparse_transp_vector_col.JA);
            return rc;
        }

        printf("\nВвод значений ненулевых элементов вектора-столбца\n");
        if ((rc = fill_matrix_by_input(&std_vector_col, cnz_vector)) != 0)
        {
            matrix_free(std_matrix.matrix, std_matrix.count_row);
            matrix_free(std_vector_col.matrix, std_vector_col.count_row);
            matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
            free(sparse_matrix.A);
            free(sparse_matrix.JA);
            free(sparse_vector_col.A);
            free(sparse_vector_col.JA);
            free(sparse_transp_vector_col.A);
            free(sparse_transp_vector_col.JA);
            return rc;
        }
        break;
    default:
        break;
    }

    long double std_end, std_begin;

    std_begin = microseconds_now();
    std_matrix_mult(&std_matrix, &std_vector_col, &std_vector_col_res);
    std_end = microseconds_now() - std_begin;

    cnz_res = get_count_no_zero(&std_vector_col_res);

    // выделяю память под результирующую разреженную матрицу
    if ((rc = array_alloc(&sparse_vector_col_res.A, cnz_res)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
        free(sparse_matrix.A);
        free(sparse_matrix.JA);
        free(sparse_vector_col.A);
        free(sparse_vector_col.JA);
        free(sparse_transp_vector_col.A);
        free(sparse_transp_vector_col.JA);
        return rc;
    }
    if ((rc = array_alloc(&sparse_vector_col_res.JA, cnz_res)) != 0)
    {
        matrix_free(std_matrix.matrix, std_matrix.count_row);
        matrix_free(std_vector_col.matrix, std_vector_col.count_row);
        matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
        free(sparse_matrix.A);
        free(sparse_matrix.JA);
        free(sparse_vector_col.A);
        free(sparse_vector_col.JA);
        free(sparse_transp_vector_col.A);
        free(sparse_transp_vector_col.JA);
        free(sparse_vector_col_res.A);
        return rc;
    }
    sparse_vector_col_res.count_no_zero = cnz_res;

    if ((rc = copy_std_matrix_to_sparse_matrix(&std_matrix, &sparse_matrix, cnz_matrix)) != 0)
        return rc;
    if ((rc = copy_std_matrix_to_sparse_matrix(&std_vector_col, &sparse_vector_col, cnz_vector)) != 0)
        return rc;

    if ((rc = transpose_vector_col(&std_vector_col, &transp_vector_col)))
        return rc;
    if ((rc = copy_std_matrix_to_sparse_matrix(&transp_vector_col, &sparse_transp_vector_col, cnz_vector)) != 0)
        return rc;

    //выделяю память для результирующего разряженного вектора
    // (для матриц слагаемых выделяется при копировании)
    if ((sparse_vector_col_res.IA.next_elem = create_linked_list(0)) == NULL)
    {
        return ERR_ALLOC_MEMORY;
    }

    long double sparse_begin, sparse_end;

    sparse_begin = microseconds_now();
    sparse_mult(&sparse_matrix, &sparse_transp_vector_col, &sparse_vector_col_res);
    sparse_end = microseconds_now() - sparse_begin;

    printf("\nОценка эффективности работы двух алгоритмов умножения матриц:\n");
    if (std_matrix.count_row * std_matrix.count_col > MAX_PRINT_MATIRX || std_vector_col.count_row > MAX_PRINT_VECTOR)
    {
        printf("\nИсходная матрица не будет выведена на экран, "
               "поскольку количество элементов в матрице превышает 225\n");
        printf("\nИсходная вектор-столбец не будет выведен на экран, "
               "поскольку количество элементов в векторе-столбце превышает 20\n");
    }
    else
    {
        printf("\nВведенная матрица:\n");
        print_std_matrix(&std_matrix);
        printf("\nВведенный вектор:\n");
        print_std_matrix(&std_vector_col);
    }

    print_mult_result(&std_vector_col_res, &sparse_vector_col_res);
    print_result(std_matrix, sparse_matrix, std_end, sparse_end);

    matrix_free(std_matrix.matrix, std_matrix.count_row);
    matrix_free(std_vector_col.matrix, std_vector_col.count_row);
    matrix_free(std_vector_col_res.matrix, std_vector_col_res.count_row);
    free(sparse_matrix.A);
    free(sparse_matrix.JA);
    free(sparse_vector_col.A);
    free(sparse_vector_col.JA);
    free(sparse_transp_vector_col.A);
    free(sparse_transp_vector_col.JA);
    free(sparse_vector_col_res.A);
    
    return rc;

}