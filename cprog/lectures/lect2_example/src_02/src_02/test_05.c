/*
Слайды 4 - 6.
*/

#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
    return a + b;
}

int (*get_action_1(char ch))(int, int)
{
    if (ch == '+')
        return add;

    return NULL;
}

typedef int (*ptr_action_t)(int, int);

ptr_action_t get_action_2(char ch)
{
    if (ch == '+')
        return add;

    return NULL;
}

int main(void)
{
    int (*p1)(int, int) = add;
    int (*p2)(int, int) = &add;
    int (*p3)(int, int) = *add;
    int (*p4)(int, int) = ****add;
    int (*p5)(int, int) = get_action_1('+');
    int (*p6)(int, int) = get_action_2('+');

    if (p1 == add)
        printf("p1 points to add\n");

    (void) p1;
    (void) p2;
    (void) p3;
    (void) p4;            
    (void) p5;
    (void) p6;            

    return 0;
}
