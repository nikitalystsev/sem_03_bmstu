#include "filter.h"


void get_index_max_and_min(const int *pb_src,
const int *pe_src,
int *const ind_max,
int *const ind_min)
{
    int index = 0;
    int value_max = *pb_src, value_min = *pb_src;

    for (const int *ptr_cur = pb_src; ptr_cur < pe_src; ptr_cur++, index++)
    {
        if (*ptr_cur > value_max)
        {
            *ind_max = index;
            value_max = *ptr_cur;
        }
        else if (*ptr_cur < value_min)
        {
            *ind_min = index;
            value_min = *ptr_cur;
        }
    }
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (pb_src == NULL || pe_src == NULL || pb_src > pe_src)
        return ERR_NO_DATA;

    int ind_max = 0, ind_min = 0;

    get_index_max_and_min(pb_src, pe_src, &ind_max, &ind_min);

    if (ind_max == ind_min)
        return ERR_NO_DATA;

    if (ind_max < ind_min)
        swap(&ind_max, &ind_min, sizeof(int));

    int count_elements_new_array = ind_max - ind_min - 1;

    if (count_elements_new_array == 0)
        return ERR_NO_DATA;
    
    *pb_dst = malloc(count_elements_new_array * sizeof(int));

    if (*pb_dst == NULL)
        return ERR_ALLOC_MEM;

    *pe_dst = *pb_dst + count_elements_new_array;

    int *ptr_narray = *pb_dst;

    for (const int *ptr_cur = pb_src + ind_min + 1; ptr_cur < pb_src + ind_max; ptr_cur++, ptr_narray++)
        *ptr_narray = *ptr_cur;

    return EXIT_SUCCESS;
}
