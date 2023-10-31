#include <stdio.h>

#define N 10

void print_array(int *a, size_t n)
{
    for (size_t i = 0; i < n; i++)
        printf("%d ", a[i]);
}

int array_init(int *a, size_t n)
{
    int numb;
    int rc;
    for (size_t i = 0; i < n; i++)
    {
        rc = scanf("%d", &numb);
        if (rc != 1)
        {
            printf("Error");
            return 1;
        }    
        a[i] = numb;
    }
    return 0;
}



int left_shift(int *a, int *n)
{
    int i = 0;
    while (i < *n)
    {
        if (a[i] == a[i + 1] && a[i + 1] == a[i + 2])
        {
            a[i] = a[i] + a[i + 1];
            a[i + 1] = a[i + 2];
            (*n)--;
        }    
        else if (a[i] == a[i + 1])
        { 
            a[i] = a[i] + a[i + 1];
            i++;
            while (i < *n)
            {
               a[i] = a[i + 1];
              
               i++;
            }
            (*n)--;
        }

        i++;
    }
    return 0;
}

int right_shift(int *a, int n)
{
    int i = n - 1;
  	while (i >= 0)
    	{
        	if (a[i] == a[i - 1] && a[i - 1] == a[i - 2])
        	{
            	a[i] = a[i] + a[i - 1];
            	a[i - 1] = a[i - 2];
            	n = n - 2;
            }
        	else if (a[i] == a[i - 1])
        	{
            	a[i] = a[i] + a[i - 1];
            	n--;
            }
        	i--;
    	}
    	return 0;
}
int main(void)
{
    int a[N];
    int rc;
    int n;
    int count_oper;
    int oper[N];

    rc = scanf("%d", &n);
    if (rc != 1 || n < 0 || n > N)
        return 1;

    rc = array_init(a, n);
    if (rc == 1)
       return 1;
    printf("Исходный массив\n");
    print_array(a, n);
    rc = scanf("%d", &count_oper);
    if (rc != 1 || count_oper < 0)
        return 1;

    rc = array_init(oper, count_oper);
    if (rc == 1)
        return 1;
        
    
    for (int i = 0; i < count_oper; i++)
    {
        if (oper[i] == -1)
            left_shift(a, &n);
        else if (oper[i] == 1)
            right_shift(a, n);
    }
    
    print_array(a, n);
    return 0;
}
