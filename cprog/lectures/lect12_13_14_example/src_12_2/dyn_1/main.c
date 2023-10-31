#include <stdio.h>
#include <stdlib.h>

__declspec(dllimport) void __cdecl arr_form(int *arr, int n);

__declspec(dllimport) void __cdecl arr_print(const int *arr, int n);

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
