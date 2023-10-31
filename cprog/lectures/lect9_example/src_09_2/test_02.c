/*
Слайд 7
*/

#include <stdio.h>
#include <math.h>

#define EPS	1.0e-7

double avg(double a, ...)
{
    int n = 0;
    double *p_d = &a;
    double sum = 0.0;

    while (fabs(*p_d) > EPS)
    {
        sum += *p_d;
        n++;

        p_d++;
    }

    if (!n)
        return 0;

    return sum / n;
}

int main(void)
{
    double a = 
         avg(1.0, 2.0, 3.0,
                      4.0, 0.0);

    printf("a = %5.2f\n", a);

    return 0;
}

