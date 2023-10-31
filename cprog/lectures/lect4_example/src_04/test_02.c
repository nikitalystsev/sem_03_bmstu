/*
Слайды 9, 11
*/

#include <stdio.h>
#include <stdlib.h>


void free_matrix(double **data, size_t n);


double** allocate_matrix(size_t n, size_t m)
{
    double **data;

    data = calloc(n, sizeof(double*));
    if (!data)
        return NULL;

    for (size_t i = 0; i < n; i++)
    {
        data[i] = malloc(m * sizeof(double));
        if (!data[i])
        {
            free_matrix(data, n);

            return NULL;
        }
    }

    return data;
}


void free_matrix(double **data, size_t n)
{
    for (size_t i = 0; i < n; i++)
        free(data[i]);

    free(data);
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
    free_matrix(mtr, n);

    return 0;
}
