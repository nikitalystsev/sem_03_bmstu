/*
Слайд 26 (в этом примере есть ошибки!)
*/

#include <stdio.h>
#include <stdlib.h>


double** allocate_matrix(int n, int m)
{
    double **matrix = malloc(n * sizeof(double*) +
                                m * sizeof(double));
    if (matrix == NULL)
        free(matrix);

    matrix[0] = matrix + n;
    for (int i = 1; i < n; i++)
        matrix[i] = matrix[0] + m * i;

    return matrix;
}

