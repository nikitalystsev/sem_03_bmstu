#include <stdio.h>

#define MAX_SIZE 10

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define ERR_EXPR_NO_CALC 3
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

int array_init(int *ptr_start, int *ptr_end)
{
    int rc;
    for (int *pcur = ptr_start; pcur < ptr_end; pcur++)
    {
        rc = scanf("%d", pcur);
        if (rc != 1)
        {
            printf("Error: wrong input");
            return ERR_WRONG_INPUT;
        }
    }
    return SUCCESS;
}

void unique_elements(int *ptr_start, int *ptr_end)
{
    int count_elem = 0;
    int diff = 0;
    for (int *pcur = ptr_start; pcur < ptr_end; pcur++)
    {
        for (int *pcur2 = pcur; pcur2 < ptr_end; pcur2++)
        {
            if (*pcur == *pcur2)
                count_elem++;
            if (count_elem > 1) 
                break;
        }
        if (count_elem == 1)
            diff++;
        count_elem = 0;
    }

    printf("%d", diff);
}

int main(void)
{
    int a[MAX_SIZE];
    int n;
    int rc;
    int *ptr_start = a;
    int *ptr_end = a;

    rc = get_dimension(&n);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;
    else if (rc == ERR_WRONG_DIMENSION)
        return ERR_WRONG_DIMENSION;

    ptr_end = a + n; 

    rc = array_init(ptr_start, ptr_end);
    if (rc == ERR_WRONG_INPUT)
        return ERR_WRONG_INPUT;

    unique_elements(ptr_start, ptr_end);

    return SUCCESS;
}
