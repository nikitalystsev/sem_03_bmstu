#include <stdio.h>
#include "arr_lib.h"

__declspec(dllexport) void __cdecl arr_form(int *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}

__declspec(dllexport) void __cdecl arr_print(const int *arr, int n)
{
    printf("Array:\n");

    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}
