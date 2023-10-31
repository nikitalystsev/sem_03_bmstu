#include <stdio.h>
#include <assert.h>
#include "stack_0.h"

int main(void)
{
    int     i;
    int     rc;

    make_empty();

    i = 0;
    for (i = 0; !is_full() && i < 10; i++)
    {
        rc = push(i);

        assert(rc == 0);
    }

    while (!is_empty())
    {
        rc = pop(&i);

        assert(rc == 0);

        printf("%d\n", i);
    }

    return 0;
}
