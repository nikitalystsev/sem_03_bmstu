/*
Слайд 10
*/

#include <stdarg.h>
#include <stdio.h>

double avg(int n, ...)
{
    va_list vl;
    double num;
    double sum = 0.0;

    if (!n)
        return 0;

    va_start(vl, n);

    for (int i = 0; i < n; i++)
    {
        num = va_arg(vl, double);
        sum += num;
    }

    va_end(vl);

    return sum / n;
}

int main(void)
{
    double a = 
      avg(4, 1.0, 2.0, 3.0, 4.0);

    printf("a = %5.2f\n", a);

    return 0;
}

