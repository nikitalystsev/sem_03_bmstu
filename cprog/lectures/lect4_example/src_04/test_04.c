/*
Слайд 24
*/

#include <stdio.h>
#include <stdlib.h>


double** allocate_matrix(size_t n, size_t m)
{
    double **data = malloc(n * sizeof(double*) + n * m * sizeof(double));
    if (!data)
        return NULL;

    for(size_t i = 0; i < n; i++)
        data[i] = (double*)
				((char*) data + n * sizeof(double*) + i * m * sizeof(double));

    return data;
}


double** allocate_matrix_2(size_t n, size_t m)
{
    double **data = malloc(n * sizeof(double*) + n * m * sizeof(double));
    if (!data)
        return NULL;

    double *elems = (double*) (data + n);
    for(size_t i = 0; i < n; i++)
        data[i] = elems + i * m;

    return data;
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
    free(mtr);

    return 0;
}
