#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*fn_form_t)(int*, int);
typedef void (*fn_print_t)(const int*, int);

int main(void)
{
    void* hlib;
    fn_form_t form;
    fn_print_t print;
    int *arr;
    int n = 5;
    int rc = 0;

    hlib = dlopen("libarr.so", RTLD_NOW);
    if (!hlib)
    {
        printf("Cannot open library. %s\n", dlerror());

        rc = -1;

        goto out;
    }

    printf("Library handle is %p.\n", hlib);

    arr = malloc(sizeof(int) * n);
    if (!arr)
    {
        printf("Memory allocation error.\n");

        rc = -2;

        goto free_lib;
    }

    form = (fn_form_t) dlsym(hlib, "arr_form");
    if (!form)
    {
        printf("Can not load function. %s\n", dlerror());

        rc = -3;

        goto free_mem;
    }

    printf("arr_form function is located at address %p.\n", form);

    print = (fn_print_t) dlsym(hlib, "arr_print");
    if (!print)
    {
        printf("Can not load function. %s\n", dlerror());

        rc = -3;

        goto free_mem;
    }

    printf("arr_print function is located at address %p.\n", print);

    form(arr, n);

    print(arr, n);

free_mem:
    free(arr);

free_lib:
    dlclose(hlib);

out:
    return rc;
}
