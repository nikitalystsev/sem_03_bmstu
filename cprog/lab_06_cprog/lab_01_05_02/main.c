#include <stdio.h>
#define FIB0 0
#define FIB1 1
#define MAX_FIBN_FOR_INT 46
#define SUCCESS 0
#define ERROR 1
#define CORRECT_INPUT 1

int fib_count(int n)
{
    int fib_0 = 0, fib_1 = 1;
    int fib_n;
    int i = 2;

    while (i <= n)
    {
        fib_n = fib_0 + fib_1;
        fib_0 = fib_1;
        fib_1 = fib_n;
        i++;
    }
    return fib_n;
}

void print_fib(int n)
{
    if (n == 0)
        printf("%d\n", FIB0);
    else if (n == 1)
        printf("%d\n", FIB1);
    else     
    {        
        int fibn = fib_count(n);
        printf("%d\n", fibn);
    }
}

int main(void)
{
    int n;
    int rc;	   
 
    puts("Enter number:");
    rc = scanf("%d", &n);

    if ((rc != CORRECT_INPUT) || (n < 0) || (n > MAX_FIBN_FOR_INT))
    {
        printf("Error: negative input");
        return ERROR;
    }

    print_fib(n);
    return SUCCESS;
}
