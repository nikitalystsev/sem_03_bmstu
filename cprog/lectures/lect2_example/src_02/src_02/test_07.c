/*
Слайд 8
*/

#include <assert.h>
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

int mul(int a, int b)
{
    return a * b;
}

int div(int a, int b)
{
    assert(b);

    return a / b;
}

int main(void)
{
    int a = 4, b = 5, choise = 1, result;

    switch (choise)
    {
        case 0:
            result = add(a, b);
            break;
        case 1:
            result = sub(a, b);
            break;
        case 2:
            result = mul(a, b);
            break;
        case 3:
            result = div(a, b);
            break;
        default:
            assert(0);
    }

    printf("Result is %d\n", result);
 
    return 0;
}
