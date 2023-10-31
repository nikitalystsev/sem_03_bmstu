/*
Слайд 5
*/

#include <stdio.h>

double avg(int n, ...)
{
    int i;
    int *p_i = &n;
    double *p_d = (double*) (p_i + 1);
    double sum = 0.0;

    if (!n)
        return 0;

    for (i = 0; i < n; i++, p_d++)
        sum += *p_d;

    return sum / n;
}

int main(void)
{
    double a = avg(4, 1.0, 2.0, 3.0, 4.0);

    printf("a = %5.2f\n", a);

    return 0;
}

