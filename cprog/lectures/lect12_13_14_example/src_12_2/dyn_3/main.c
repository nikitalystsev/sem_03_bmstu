#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// ���� ������� �������������� �� DLL
typedef void (__cdecl *fn_form_t)(int*, int);
typedef void (__cdecl *fn_print_t)(const int*, int);

int main(void)
{
    HMODULE hlib;
    fn_form_t form;
    fn_print_t print;
    int *arr;
    int n = 5;
    int rc = 0;

    // �������� ������������ ����������
    hlib = LoadLibrary("arr.dll");
    if (!hlib)
    {
        printf("Cannot open library.\n");

        rc = -1;

        goto out;
    }

    // ����������� �����, �� �������� ��������� ����������
    printf("Library is loaded at address %p.\n", hlib);

    arr = malloc(sizeof(int) * n);
    if (!arr)
    {
        printf("Memory allocation error.\n");

        rc = -2;

        goto free_lib;
    }

    // ������� ����� ������� "arr_form"
    form = (fn_form_t) GetProcAddress(hlib, "arr_form");
    if (!form)
    {
        printf("Can not load function.\n");

        rc = -3;

        goto free_mem;
    }

    // ����������� ����� ������� "arr_form"
    printf("arr_form function is located at address %p.\n", form);

    // ������� ����� ������� "arr_print"
    print = (fn_print_t) GetProcAddress(hlib, "arr_print");
    if (!print)
    {
        printf("Can not load function.\n");

        rc = -3;

        goto free_mem;
    }

    // ����������� ����� ������� "arr_print"
    printf("arr_print function is located at address %p.\n", print);

    form(arr, n);

    print(arr, n);

free_mem:
    free(arr);

free_lib:
    FreeLibrary(hlib);

out:
    return rc;
}
