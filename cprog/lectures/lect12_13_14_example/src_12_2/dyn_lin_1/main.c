#include <stdio.h>
#include <stdlib.h>
#include "arr_lib.h"

int main(void)
{
    int *arr;
    int n = 5;

    arr = malloc(sizeof(int) * n);
    if (!arr)
    {
        printf("Memory allocation error.\n");

        return -1;
    }

    arr_form(arr, n);

    arr_print(arr, n);

    free(arr);

    return 0;
}
