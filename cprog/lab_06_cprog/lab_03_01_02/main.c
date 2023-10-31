#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 10
#define MAX_COLUMN 10
#define MAX_SIZE 10

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define SUCCESS 0

void print_array(const int *const array, size_t m)
{
    for (size_t i = 0; i < m; i++)
        printf("%d ", array[i]);
}

int get_dimensions(size_t *const n, size_t *const m)
{
    puts("Enter count elements and elem array:");
    int rc = scanf("%lu %lu", n, m); 
    if (rc != 2)
    {
        printf("Error: wrong input");
        return ERR_WRONG_INPUT; 
    }
    if (*n <= 0 || *n > MAX_SIZE)
    {
        printf("Error: wrong dimension");
        return ERR_WRONG_DIMENSION;
    }
    if (*m <= 0 || *m > MAX_SIZE)
    {
        printf("Error: wrong dimension");
        return ERR_WRONG_DIMENSION;
    }

    return SUCCESS;
}

int matrix_init(int matrix[][MAX_COLUMN], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++) 
        {
            int numb;
            int rc = scanf("%d", &numb);
            if (rc != 1)
            {
                printf("Error: wrong input");
                return ERR_WRONG_INPUT;
            }
            matrix[i][j] = numb;
        }

    return SUCCESS;
}

int array_init(int matrix[][MAX_COLUMN], size_t n, size_t m, int *array)
{
    for (size_t j = 0; j < m; j++)
    {
        int flag = 0;
        for (size_t i = 0; i < n - 1; i++)
            if (matrix[i][j] * matrix[i + 1][j] >= 0)
            {
                flag = 0;
                break;
            }
            else 
                flag = 1;
        if (flag)
            array[j] = 1;
        else
            array[j] = 0;
    }

    return SUCCESS;
}

int main(void)
{
    size_t n, m;
    int matrix[MAX_ROW][MAX_COLUMN];
    int array[MAX_SIZE];

    int rc = get_dimensions(&n, &m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;

    rc = matrix_init(matrix, n, m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;

    array_init(matrix, n, m, array);
    print_array(array, m);

    return SUCCESS;
}
