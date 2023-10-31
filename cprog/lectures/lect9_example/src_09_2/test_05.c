/*
Слайд 11
*/

#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#define EPS	1.0e-7

double avg(double a, ...)
{
    va_list vl;
    int n = 0;
    double num, sum = 0.0;

    va_start(vl, a);
    num = a;

    while (fabs(num) > EPS)
    {
        sum += num;
        n++;
        num = va_arg(vl, double);
    }

    va_end(vl);

    if(!n)
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

