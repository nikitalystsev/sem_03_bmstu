#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW 20
#define MAX_COLUMN 20
#define MAX_SIZE 10

#define RADIX 10

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define NO_CHECK_MATRIX_STRING 3
#define NO_CHECK_ODD_SUM 3
#define SUCCESS 0

void print_array(const int *const array, size_t m)
{
    for (size_t i = 0; i < m; i++)
        printf("%d ", array[i]);
}

void print_matrix(int (*const matrix)[MAX_COLUMN], size_t n, size_t m)
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

int check_odd_sum_of_digits(int elem)
{
    int sum = 0;
    while (elem != 0)
    {
        sum += elem % RADIX;
        elem /= RADIX;
    }
    if (sum % 2 != 0)
        return SUCCESS;
    return NO_CHECK_ODD_SUM;
}

int check_string_matrix(const int *const string, size_t m)
{
    int count = 0;
    for (size_t i = 0; i < m && count < 2; i++)
    {
        int rc = check_odd_sum_of_digits(string[i]);
        if (rc == SUCCESS)
            count++;
    }
    if (count >= 2)
        return SUCCESS;
    return NO_CHECK_MATRIX_STRING;
}

void replace_row(int *const row, size_t m)
{
    for (size_t i = 0; i < m; i++)
        row[i] = -1;
}

void copy(int *const array1, int *const array2, size_t m)
{
    for (size_t i = 0; i < m; i++)
        array1[i] = array2[i];
}

void insert_row(int matrix[][MAX_COLUMN], size_t *const n, size_t m, size_t insert_index)
{   
    size_t end = *n;
    while (end > insert_index)
    {
        copy(matrix[end], matrix[end - 1], m);
        end--;
    }
    replace_row(matrix[insert_index], m);
    (*n)++;
}

void check_row_matrix(int matrix[][MAX_COLUMN], size_t  *const n, size_t m)
{
    for (size_t i = 0; i < *n; i++)
    {
        int rc = check_string_matrix(matrix[i], m);
        if (rc == SUCCESS)
        {
            insert_row(matrix, n, m, i);
            i++;
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
    size_t n, m;

    int rc = get_dimensions(&n, &m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;

    rc = matrix_init(matrix, n, m);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;

    check_row_matrix(matrix, &n, m);
    print_matrix(matrix, n, m);

    return SUCCESS;
}
