#include "filter.h"

void get_index_max_and_min(const int *pb_src, const int *pe_src,
int *const ind_max, int *const ind_min)
{
    int index = 0;
    int value_max = *pb_src, value_min = *pb_src;

    for (const int *ptr_cur = pb_src; ptr_cur < pe_src; ptr_cur++, index++)
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

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    if (!pb_src || !pe_src || pb_src > pe_src)
        return ERR_NO_DATA;

    int ind_max = 0, ind_min = 0;
    get_index_max_and_min(pb_src, pe_src, &ind_max, &ind_min);

    if (ind_max == ind_min)
        return ERR_NO_DATA;

    if (ind_max < ind_min)
        swap(&ind_max, &ind_min, sizeof(int));

    int *tmp_dst = *pb_dst;

    const int *ptr_ind_min = pb_src + ind_min + 1;
    const int *ptr_ind_max = pb_src + ind_max;

    for (const int *ptr_cur = ptr_ind_min;
         ptr_cur < ptr_ind_max && tmp_dst < *pe_dst; ptr_cur++, tmp_dst++)
        *tmp_dst = *ptr_cur;

    return EXIT_SUCCESS;
}
