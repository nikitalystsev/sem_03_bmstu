#include "check_argc.h"

int check_argc(int argc, char const *argv[])
{
    if (argc == 3 && strcmp(argv[1], "st") == 0)
        return 1;
    else if (argc == 5 && strcmp(argv[1], "ft") == 0)
        return 2;
    else if (argc == 3 && strcmp(argv[1], "dt") == 0)
        return 3;
    else
        return ERR_NO_VALID_PARAMETERS;
}
