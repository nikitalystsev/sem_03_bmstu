#include "defines.h"
#include "create_array.h"
#include "filter.h"
#include "mysort.h"
#include "param_check.h"
#include "write_numbers_to_file.h"

int main(int argc, char const *argv[])
{
    FILE *file = NULL;
    int *pb_src = NULL, *pe_src = NULL;
    int *pb_dst = NULL, *pe_dst = NULL;
    int *pb_cur = NULL, *pe_cur = NULL;

    int rc = 0;
    int count_elem = 0;

    if ((rc = check_argc(argc, argv)) != 0)
        return rc;

    if ((rc = create_array(file, argv[1], &pb_src, &pe_src)) != 0)
        goto free;

    if (argc == PARAM_NO_FILTER)
        pb_cur = pb_src, pe_cur = pe_src;

    if (argc == PARAM_FILTER)
    {
        int ind_max = 0, ind_min = 0;
        get_index_max_and_min(pb_src, pe_src, &ind_max, &ind_min);

        if ((rc = check_indexes(&ind_min, &ind_max)) != 0)
            goto free;

        int count_for_filter = ind_max - ind_min - 1;

        if (count_for_filter == 0)
            return ERR_NO_DATA;

        pb_dst = malloc(count_for_filter * sizeof(int));

        if (!pb_dst)
            return ERR_ALLOC_MEM;

        pe_dst = pb_dst + count_for_filter;

        if ((rc = key(pb_src, pe_src, &pb_dst, &pe_dst)) != 0)
            goto free;

        pb_cur = pb_dst, pe_cur = pe_dst;
    }

    count_elem = get_count_elements(pb_cur, pe_cur);

    if (count_elem == 0)
    {
        rc = ERR_NO_DATA;
        goto free;
    }

    mysort(pb_cur, count_elem, sizeof(int), compare);

    if ((rc = write_numbers_to_file(file, argv[2], pb_cur, pe_cur)) != 0)
        goto free;

    free:
        free(pb_src);
        free(pb_dst);

    return rc;
}
