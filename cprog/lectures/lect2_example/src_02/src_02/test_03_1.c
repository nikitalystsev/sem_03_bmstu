/*
Слайд 2
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>


typedef double (*func_t)(double);


// n - количество узлов
double trapezium(double a, double b, int n, func_t func)
{
    assert(a < b);
    assert(n > 1);
    assert(func);

    double h = (b - a) / (n - 1);
    double x = a + h;
    double s = (func(a) + func(b)) / 2.0;

    for (int i = 1; i < n - 1; i++)
    {
        s += func(x);
        x += h;
    }

    return s * h;
}


double line(double x)
{
    return x;
}


double parabola(double x)
{
    return x * x;
}


int main(void)
{
    printf("line [0 - 1] %e\n", trapezium(0.0, 1.0, 5, line));
    printf("parabola [0 - 1] %e\n", trapezium(0.0, 1.0, 15, parabola));

    return 0;
}

