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

int calc_product_row(const int *const row, size_t m)
{
    int product = 1;
    for (size_t i = 0; i < m; i++)
        product *= row[i];
    return product;
}

void swap(int *const array1, int *const array2, size_t m)
{
    for (size_t i = 0; i < m; i++)
    {
        int tmp = array1[i];
        array1[i] = array2[i];
        array2[i] = tmp;
    }
}

int bubble_sort(int matrix[][MAX_COLUMN], size_t n, size_t m)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        for (size_t j = 0; j < n - 1 - i; j++)
        {
            int product1 = calc_product_row(matrix[j], m);
            int product2 = calc_product_row(matrix[j + 1], m);
            if (product1 > product2)
                swap(matrix[j], matrix[j + 1], m);
        }
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

int main(void)
{
    size_t n, m;
    int matrix[MAX_ROW][MAX_COLUMN];

    int rc = get_dimensions(&n, &m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;

    rc = matrix_init(matrix, n, m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;

    rc = bubble_sort(matrix, n, m);
    print_matrix(matrix, n, m);

    return SUCCESS;
}
