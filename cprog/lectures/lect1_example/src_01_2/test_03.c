/*
Слайд 13
*/

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    int *a = malloc(0);

    printf("a %p\n", (void*) a);

    printf("%d\n", *a);

    *a = 10;

    return 0;
}