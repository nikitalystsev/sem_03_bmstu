#include <stdio.h>
#include <math.h>
#define SUCCESS 0
#define ERROR 1
#define SUMMA_NO_CALC 2
#define CORRECT_INPUT 1

int count_summa(void)
{
    double summa = 0;
    double xn = 0;
    int n = 1;
    int rc;
    
    puts("Enter func argument:");
    rc = scanf("%lf", &xn);

    if (xn < 0)
    {  
        printf("Error: no clalculate");
        return SUMMA_NO_CALC;
    }
    while (xn >= 0)
    {  
        summa += sqrt(n + xn);
        rc = scanf("%lf", &xn);
        if (rc != CORRECT_INPUT)
        {
            printf("Error: wrong input");
            return ERROR;
        }
 
        n++;    
    }

    summa /= (n - 1);
    printf("%lf", summa);
    return SUCCESS;
}

int main(void)
{
    int rc;
    
    rc = count_summa();
    if (rc == ERROR)
        return ERROR;
    else if (rc == SUMMA_NO_CALC)
        return SUMMA_NO_CALC;
    return SUCCESS;
}
