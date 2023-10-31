#include "param_check.h"

int check_argc(int argc, char const *argv[])
{
    if (argc < PARAM_NO_FILTER || argc > PARAM_FILTER)
        return ERR_NO_VALID_PARAM;
        
    if (argc == PARAM_FILTER && strcmp(argv[3], "f") != 0)
        return ERR_NO_VALID_PARAM;

    return EXIT_SUCCESS;
}
