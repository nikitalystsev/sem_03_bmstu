#include <stdio.h>
#include <assert.h>
#include "stack.h"

int main(void)
{
    stack_t s;
    int     i;
    int     rc;

    s = create();

    if (!s)
    {
        fprintf(stderr, "Memory allocation error.\n");
        return 1;		
    }

    for (i = 0; !is_full(s) && i < 10; i++)
    {
        rc = push(s, i);

        assert(rc == 0);
    }

    while (!is_empty(s))
    {
        rc = pop(s, &i);

        assert(rc == 0);

        printf("%d\n", i);
    }

    destroy(s);

    return 0;
}
