/*
Слайд 3
*/

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double *data;
    size_t n = 3, m = 2, p = 1;

    // Выделение памяти под "матрицу"
    data = malloc(n * m * sizeof(double));
    if (data)
    {
        // Работа с "матрицей"

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
                // Обращение к элементу i, j
                data[i * m + j] = p + j;

            p *= 10;
        }

        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < m; j++)
                printf(" %5.1f", data[i * m + j]);

            printf("\n");
        }

        // Освобождение памяти
        free(data);
    }

    return 0;
}