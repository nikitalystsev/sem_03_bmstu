#include "arr_func.h"

static void cyclic_shift_left_by_1(int *array, int n)
{
    int tmp = array[0];

    for (int i = 0; i < n - 1; i++)
        array[i] = array[i + 1];

    array[n - 1] = tmp;
}

void cyclic_shift_left_by_k(int *array, int n, int k)
{
    k = (k % n);

    for (int i = 0; i < k; i++)
        cyclic_shift_left_by_1(array, n);
}

static int is_square(int number)
{
    if (sqrt(number) - (int)sqrt(number) < EPS)
        return 1;

    return 0;
}

int get_count_square(int *array, int n)
{
    int count_square = 0;

    for (int i = 0; i < n; i++)
        if (is_square(array[i]))
            count_square++;

    return count_square;
}

void copy_arr_by_square(int *array, int n, int *new_array, int new_n)
{
    int ind_new_arr = 0;

    for (int i = 0; i < n && ind_new_arr < new_n; i++)
        if (is_square(array[i]))
            new_array[ind_new_arr++] = array[i];
}
