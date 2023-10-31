#include <stdio.h>
#include "arr_lib.h"

void arr_form(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

void arr_print(const int *arr, int n)
{
    printf("Array:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}
