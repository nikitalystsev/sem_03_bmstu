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

void print_matrix(int matrix[][MAX_COLUMN], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
    {
        print_array(matrix[i], m);
        printf("\n");
    }
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

void matrix_init(int matrix[][MAX_COLUMN], int n, int m)
{
    int elem = 1;
    int j = m - 1;
    while (j >= 0)
    {
        int i = n - 1;
        while (i >= 0)
        {
            matrix[i][j] = elem;
            elem++;
            i--;
        }
        
        j--;

        if (j == -1)
            break;

        i = 0;
        while (i < n)
        {
            matrix[i][j] = elem;
            elem++;
            i++;
        }

        j--;
    }
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

    matrix_init(matrix, n, m);
    print_matrix(matrix, n, m);
    
    return SUCCESS;
}
