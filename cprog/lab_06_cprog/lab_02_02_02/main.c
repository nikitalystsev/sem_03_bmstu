#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

#define SCALE_OF_NOTATION 10

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define ERR_NO_REQUARED_ITEMS 3
#define ERR_NO_CHECK_NUMBER 4
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

int check_number(int number)
{
    int start = number % SCALE_OF_NOTATION;
    int end = number % SCALE_OF_NOTATION;

    while (number > 0)
    {
        end = number % SCALE_OF_NOTATION;
        number /= SCALE_OF_NOTATION;
    }    

    if (start == end)
        return SUCCESS;

    return ERR_NO_CHECK_NUMBER;
}

int copy_array(int *old_array, int *new_array, size_t size, int *count)
{
    int rc;

    for (size_t i = 0; i < size; i++)
    {
        rc = check_number(abs(old_array[i]));
        if (rc == SUCCESS)
        {
            new_array[*count] = old_array[i];
            (*count)++;           
        }
    }
    
    if (*count == 0)
    {
        printf("Error: no required items");
        return ERR_NO_REQUARED_ITEMS;
    }

    return SUCCESS;
} 

int main(void)
{
    int old_a[MAX_SIZE];
    int new_a[MAX_SIZE];
    int rc;
    int size;
    int count = 0;

    rc = get_dimension(&size);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;

    rc = array_init(old_a, size);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;

    rc = copy_array(old_a, new_a, size, &count);
    if (rc == ERR_NO_REQUARED_ITEMS)
        return ERR_NO_REQUARED_ITEMS;

    print_array(new_a, count);

    return SUCCESS;
}
