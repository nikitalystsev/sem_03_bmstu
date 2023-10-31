/*
Слайды 17, 19
*/

#include <stdio.h>
#include <stdlib.h>


double** allocate_matrix(size_t n, size_t m)
{
    double **ptrs, *data;

    ptrs = malloc(n * sizeof(double*));
    if (!ptrs)
        return NULL;

    data = malloc(n * m * sizeof(double));
    if (!data)
    {
        free(ptrs);

        return NULL;
    }

    for (size_t i = 0; i < n; i++)
        ptrs[i] = data + i * m;

    return ptrs;
}


void free_matrix(double **ptrs)
{
    // ВНИМАНИЕ
    // Источник потенциальной ошибки, если строки матрицы будут меняться местами
    free(ptrs[0]);

    free(ptrs);
}


int main(void)
{
    size_t n = 3, m = 2, p = 1;
    // Выделение памяти под матрицу
    double **mtr = allocate_matrix(n, m);

    if (!mtr)
    {
        printf("Memory allocation error!\n");

        return -1;
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            mtr[i][j] = p + j;

        p *= 10;
    }

    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++)
            printf(" %5.1f", mtr[i][j]);

        printf("\n");
    }

    // Освобождение памяти
    free_matrix(mtr);

    return 0;
}
