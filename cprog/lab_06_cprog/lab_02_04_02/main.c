#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10
#define ARRAY_OUT_OF_BOUNDS 11
#define ERR_FIRST_WRONG_ELEM 1
#define OVERFLOY 100
#define SUCCESS 0

void print_array(int *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int selection_sort(int *a, size_t n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        int min_elem = a[i];
        size_t min_ind = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (a[j] < min_elem)
            {
                min_elem = a[j];
                min_ind = j;
            }
        }
    
        if (min_ind != i)
            swap(&a[i], &a[min_ind]);  
    }
    return SUCCESS; 
}

int array_init(int *a, size_t *count)
{
    int n;
    int rc;
    
    puts("Enter element array:");
    rc = scanf("%d", &n);
    if (rc != 1)
    {
        printf("Error: array not initialized");
        return ERR_FIRST_WRONG_ELEM;
    }

    a[0] = n;
    (*count)++;

    for (size_t i = 1; ; i++)
    {
        rc = scanf("%d", &n);
        if (rc != 1)
            break;

        (*count)++;

        if (*count == ARRAY_OUT_OF_BOUNDS)
            break;
        
        a[i] = n;
    }  
    return SUCCESS;
}

int main(void)
{   
    int a[MAX_SIZE];
    size_t count = 0;
    int rc;

    rc = array_init(a, &count);

    if (rc == 1)
        return ERR_FIRST_WRONG_ELEM; 

    if (count == ARRAY_OUT_OF_BOUNDS)
    {
        selection_sort(a, count - 1);
        print_array(a, count - 1);
        return OVERFLOY;
    }

    selection_sort(a, count);
    print_array(a, count);

    return SUCCESS;
}
