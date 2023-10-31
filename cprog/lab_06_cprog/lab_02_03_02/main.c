#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 10
#define EPS 1e-9

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define ERR_NO_FULL_SQUARES 3
#define ERR_ALL_ELEM_FULL_SQUARES 4
#define SUCCESS 0

void print_array(int *a, size_t size)
{
    for (size_t i = 0; i < size; i++)
        printf("%d ", a[i]);
}

int get_dimension(int *size)
{
    int rc;

    puts("Enter count elements and elem array:");
    rc = scanf("%d", size); 
    if (rc != 1)
    {
        printf("Error: wrong input");
        return ERR_WRONG_INPUT; 
    }
    if (*size < 0 || *size > MAX_SIZE)
    {
        printf("Error: wrong dimension");
        return ERR_WRONG_DIMENSION;
    }

    return SUCCESS;
}

int array_init(int *a, size_t size)
{
    int rc;
    int numb;

    for (size_t i = 0; i < size; i++)
    {
        rc = scanf("%d", &numb);
        if (rc != 1)
        {
            printf("Error: wrong input");
            return ERR_WRONG_INPUT;
        }
        a[i] = numb;
    }

    return SUCCESS;
}

int check_full_square(int number)
{
    if (((sqrt(number) - (int) sqrt(number)) < EPS) && (number >= 0))
        return SUCCESS;
    return ERR_NO_FULL_SQUARES;
}

int del_full_squares(int *a, size_t *size)
{   
    size_t i = 0; 
    int rc;

    while (i < *size)
    {   
        rc = check_full_square(a[i]);
        if (rc == SUCCESS)
        {
            for (size_t j = i; j < *size; j++)
            {      
                a[j] = a[j + 1];
            }
            (*size)--;
            a[*size] = 0;
        }
        else
            i++;
    }    

    if (*size == 0)
    {
        printf("Error: all array elements are perfect squares");
        return ERR_ALL_ELEM_FULL_SQUARES;
    }

    return SUCCESS;
} 

int main(void)
{
    int a[MAX_SIZE];
    int rc;
    int n;
    size_t size;

    rc = get_dimension(&n);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;
    
    size = n;

    rc = array_init(a, size);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    
    rc = del_full_squares(a, &size);
    if (rc == ERR_ALL_ELEM_FULL_SQUARES)
        return ERR_ALL_ELEM_FULL_SQUARES;

    print_array(a, size);

    return SUCCESS;
}
