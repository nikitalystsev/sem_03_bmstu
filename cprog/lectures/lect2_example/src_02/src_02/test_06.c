/*
Слайд 7
*/

#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    return a + b;
}

int main(void)
{
    int (*p1)(int, int) = add;
    void *p2 = NULL;
    void (*p3)(void) = NULL; 
    int a =4, b = 5;

    printf("%d + %d = %d\n", a, b, p1(a, b));

    p2 = p1;
    p1 = p2;

    printf("%d + %d = %d\n", a, b, p1(a, b));

    p3 = (void (*)(void)) p1;
    p1 = (int (*)(int, int)) p3;
    
    printf("%d + %d = %d\n", a, b, p1(a, b));

    return 0;
}
