#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define ERR_NO_NEG_ELEM 3
#define SUCCESS 0

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

int ar_mean_of_neg_elem(int *a, size_t size, double *ar_mean)
{
    int count_negative_elem = 0;
    double sum_negative_elem = 0;

    for (size_t i = 0; i < size; i++)
    {
        if (a[i] < 0)
        {
            count_negative_elem += 1;
            sum_negative_elem += a[i];
        }
    }

    if (count_negative_elem == 0)
        return ERR_NO_NEG_ELEM;

    *ar_mean = sum_negative_elem / count_negative_elem;

    return SUCCESS;
}

int main(void)
{
    int a[MAX_SIZE];
    int rc;
    int size;
    double ar_mean;

    rc = get_dimension(&size);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;

    rc = array_init(a, size);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;

    rc = ar_mean_of_neg_elem(a, size, &ar_mean);
    if (rc == ERR_NO_NEG_ELEM)
        return ERR_NO_NEG_ELEM;

    printf("%f", ar_mean);

    return SUCCESS;
}
