#include "print.h"

void print_info(void)
{
    printf("%s\n",
           "Данная программа умножает матрицу на вектор-столбец, обрабатывая их\n"
           "а) С помощью алгоритмов для обработки разреженных матриц.\n"
           "б) С помощью стандартных алгоритмов обработки матриц.\n\n"
           "В разреженном виде матрица хранится в двух массивах и одном списке: \n"
           "    А - массив ненулевых элементов;\n"
           "   JA - массив номеров столбцов для каждого элемента А;\n"
           "   IA - односвязный список, который содержит индекс;\n"
           "        каждого первого элемента очередной строки в массивах A и JA.\n"
           "\nВведите 0, если хотите сгенерировать матрицу и вектор-столбец случайно,\n"
           "или 1, если хотите ввести матрицу и вектор-столбец с клавиатуры:");
}

void print_std_matrix(const std_matrix_t *const std_matrix)
{
    for (int i = 0; i < std_matrix->count_row; i++)
    {
        for (int j = 0; j < std_matrix->count_col; j++)
        {
            printf("%4d ", std_matrix->matrix[i][j]);
        }
        printf("\n");
    }
}

void print_sparse_matrix(const sparse_matrix_t *const sparse_matrix)
{
    printf("\nЗначения ненулевых элементов (A):\n");
    for (int i = 0; i < sparse_matrix->count_no_zero; i++)
    {
        printf("%d ", sparse_matrix->A[i]);
    }
    printf("\nНомера столбцов для ненулевых элементов (JA):\n");
    for (int i = 0; i < sparse_matrix->count_no_zero; i++)
    {
        printf("%d ", sparse_matrix->JA[i]);
    }
    printf("\nМассив, содержаний описания начала каждой строки (IA):\n");
    print_linked_list(sparse_matrix->IA.next_elem);

    printf("\n");
}

void print_mult_result(const std_matrix_t *const std_vector_col_res,
                       const sparse_matrix_t *const sparse_vector_col_res)
{
    if (std_vector_col_res->count_row > MAX_PRINT_VECTOR)
    {
        printf("\nРезультат вычислений не будет выведен на экран,\n"
               "поскольку количество элементов в векторе столбце превышает 20 элементов\n");
        return;
    }

    printf("\nРезультат вычислений:\n");
    printf("\nКлассический вектор столбец:\n");
    print_std_matrix(std_vector_col_res);
    printf("\nРазреженна форма хранения результата:\n");
    print_sparse_matrix(sparse_vector_col_res);
}

void print_result(const std_matrix_t std_matrix,
                  const sparse_matrix_t sparse_matrix,
                  const long double std_mult_time,
                  const long double sparse_mult_time)
{
    printf("\nВведенная матрица имеет размеры: %d x %d. Таким образов в ней %d элементов\n",
           std_matrix.count_row, std_matrix.count_col, std_matrix.count_row * std_matrix.count_col);

    printf("\nКоличество ненулевых элементов в веденной матрице: %d\n", sparse_matrix.count_no_zero);

    printf("\nПроцент заполненности матрицы ненулевыми элементами: %.2lf%%/100%%\n",
           ((double)sparse_matrix.count_no_zero / (std_matrix.count_row * std_matrix.count_col)) * 100);
    printf("\nВремя, затраченное на умножение с "
           "помощью стандартных алгоритмов обработки матриц (микросекунды): %Lf\n",
           std_mult_time);
    printf("Время, затраченное на умножение с "
           "помощью алгоритмов обработки разреженных матриц (микросекунды): %Lf\n",
           sparse_mult_time);

    printf("\nЗанимаемый обьем памяти (байты):\n");
    printf("Обычная матрица (исходная): %lu\n",
           std_matrix.count_row * std_matrix.count_col * sizeof(int) + 2 * sizeof(int));
    printf("Разреженная матрица (исходная): %lu\n",
           2 * sparse_matrix.count_no_zero * sizeof(int) + 3 * sizeof(int) + sparse_matrix.count_row * sizeof(int));
}
