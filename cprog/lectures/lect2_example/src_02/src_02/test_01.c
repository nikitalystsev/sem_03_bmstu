/*
Слайд 2
*/

#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int mul(int a, int b)
{
    return a * b;
}

int apply(int a, int b, int (*action)(int, int))
{
    return action(a, b); // (*action)(a, b)
}

int main(void)
{
    int (*p_action)(int, int) = add; // или &add

    int a = 5, b = 4;

    printf("%d + %d = %d\n", a, b, apply(a, b, p_action));

    printf("%d * %d = %d\n", a, b, apply(a, b, mul));

    return 0;
}
