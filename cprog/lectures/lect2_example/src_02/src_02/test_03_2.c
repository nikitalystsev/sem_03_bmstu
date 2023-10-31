/*
Слайд 2
*/

#include <stdio.h>
#include <math.h>
#include <assert.h>


typedef double (*func_t)(double);


typedef double (*method_t)(double, double, int, func_t);


double integral(double a, double b, double eps, method_t meth, func_t func)
{
    assert(a < b);
    assert(0 < eps && eps < 1);
    assert(meth);
    assert(func);

    int n = 10;
    double prev, cur = meth(a, b, n, func);

    do
    {
        prev = cur;

        n *= 2;
        cur = meth(a, b, n, func);
    }
    while (fabs((cur - prev) / cur) > eps);

    printf("%d\n", n);

    return cur;
}


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
    printf("line [0 - 1] %e\n", integral(0.0, 1.0, 0.001, trapezium, line));
    printf("parabola [0 - 1] %e\n", integral(0.0, 1.0, 0.001, trapezium, parabola));

    return 0;
}

