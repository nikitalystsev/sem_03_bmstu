#include <stdio.h>
#include <assert.h>
#include "stack_1.h"

int main(void)
{
    stack_t s_1, s_2;
    int     i;
    int     rc;

    make_empty(&s_1);

    for (i = 0; !is_full(&s_1) && i < 10; i++)
    {
        rc = push(&s_1, i);

        assert(rc == 0);
    }

    printf("Stack 1\n");
    while (!is_empty(&s_1))
    {
        rc = pop(&s_1, &i);

        assert(rc == 0);

        printf("%d\n", i);
    }

    make_empty(&s_2);

    for (i = 1; !is_full(&s_2) && i < 11; i += 2)
    {
        rc = push(&s_2, i);

        assert(rc == 0);
    }

    printf("Stack 2\n");
    while (!is_empty(&s_2))
    {
        rc = pop(&s_2, &i);

        assert(rc == 0);

        printf("%d\n", i);
    }
    return 0;
}