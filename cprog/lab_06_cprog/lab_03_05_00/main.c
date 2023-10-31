#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 10
#define MAX_COLUMN 10
#define MAX_SIZE MAX_ROW * MAX_COLUMN

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define ERR_NO_PRIME_NUMBER 3
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
    if (*n <= 0 || *n > MAX_ROW)
    {
        printf("Error: wrong dimension");
        return ERR_WRONG_DIMENSION;
    }
    if (*m <= 0 || *m > MAX_COLUMN)
    {
        printf("Error: wrong dimension");
        return ERR_WRONG_DIMENSION;
    }

    return SUCCESS;
}

int check_prime_number(int elem)
{
    if (elem <= 1)
        return ERR_NO_PRIME_NUMBER;

    for (int i = 2; i < elem; i++)
        if (elem % i == 0)
            return ERR_NO_PRIME_NUMBER;
    return SUCCESS;
}

void reverse_array(int *const array, int count_elem_array)
{
    for (int i = 0; i < count_elem_array / 2; i++)
    {
        int tmp = array[i];
        array[i] = array[count_elem_array - 1 - i];
        array[count_elem_array - 1 - i] = tmp;
    }
}

int array_init(int *const array, int *const count_elem_array, int matrix[][MAX_COLUMN], size_t n, size_t m)
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < m; j++) 
        {
            int rc = check_prime_number(matrix[i][j]);
            if (rc == SUCCESS)
            {
                array[*count_elem_array] = matrix[i][j];
                (*count_elem_array)++;
            }
        }
    if (*count_elem_array == 0)
    {
        printf("Error: no prime numbers");
        return ERR_NO_PRIME_NUMBER;
    }
    return SUCCESS;
}

void insert_array_to_matrix(const int *const array, int matrix[][MAX_COLUMN], size_t n, size_t m)
{
    int index_insert_elem = 0;
    for (size_t i = 0; i < n; i++)
    {
        for (size_t j = 0; j < m; j++) 
        {
            int rc = check_prime_number(matrix[i][j]);
            if (rc == SUCCESS)
            {
                matrix[i][j] = array[index_insert_elem];
                index_insert_elem++;
            }
        }
    }
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
    int array[MAX_SIZE];
    int count_elem_array = 0;
    size_t n, m;

    int rc = get_dimensions(&n, &m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;

    rc = matrix_init(matrix, n, m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;

    rc = array_init(array, &count_elem_array, matrix, n, m);
    if (rc == ERR_NO_PRIME_NUMBER)
        return ERR_NO_PRIME_NUMBER;

    reverse_array(array, count_elem_array);
    insert_array_to_matrix(array, matrix, n, m);
    print_matrix(matrix, n, m);

    return SUCCESS;
}