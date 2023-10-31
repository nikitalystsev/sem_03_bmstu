#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_ROW 10
#define MAX_COLUMN 10
#define MAX_SIZE 10

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define ERR_NO_MAX_ELEM 3
#define ERR_VARIOUS_DIMENSION 4
#define SUCCESS 0

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

int find_max_elem(int matrix[][MAX_COLUMN], size_t n, size_t m)
{
    int max_elem = INT_MIN;
    int flag = 0;

    for (size_t i = 0; i < n; i++)
        for (size_t j = n - i; j < m; j++)
        {
            if (abs(matrix[i][j]) % 10 == 5 && max_elem < matrix[i][j])
            {
                max_elem = matrix[i][j];
                flag = 1;
            }
        }

    if (flag == 0)
        return ERR_NO_MAX_ELEM;

    printf("%d", max_elem);

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

int main(void)
{
    int matrix[MAX_ROW][MAX_COLUMN];
    size_t n, m;

    int rc = get_dimensions(&n, &m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;

    if (n != m)
        return ERR_VARIOUS_DIMENSION;

    rc = matrix_init(matrix, n, m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;

    rc = find_max_elem(matrix, n, m);
    if (rc == ERR_NO_MAX_ELEM)
        return ERR_NO_MAX_ELEM;

    return SUCCESS;
}
