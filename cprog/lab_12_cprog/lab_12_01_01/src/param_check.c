#include "param_check.h"

int check_argc(int argc, char const *argv[])
{
    if (argc < PARAM_NO_FILTER || argc > PARAM_FILTER)
        return ERR_NO_VALID_PARAM;

    if (argc == PARAM_FILTER && strcmp(argv[3], "f") != 0)
        return ERR_NO_VALID_PARAM;

    return EXIT_SUCCESS;
}

int check_indexes(int *ind_min, int *ind_max)
{
    if (*ind_max == *ind_min)
        return ERR_NO_DATA;

    if (*ind_max < *ind_min)
        swap(ind_max, ind_min, sizeof(int));
    
    return EXIT_SUCCESS;
}
