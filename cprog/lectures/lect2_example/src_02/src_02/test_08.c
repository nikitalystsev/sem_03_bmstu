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

typedef int (*ptr_action_t)(int, int);

int main(void)
{
    ptr_action_t actions[] = {add, sub, mul, div };
    int a = 4, b = 5, choise = 1;
    
    assert(0 <= choise && choise < sizeof(actions) / sizeof(actions[0]));

    printf("Result is %d\n", actions[choise](a, b));
 
    return 0;
}
