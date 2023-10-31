#include "check_argc.h"

int check_count_argc(const int argc)
{
    int rc;
    switch (argc)
    {
        case 2: rc = 0;
                break;
        default: rc = ERR_NO_VALID_PARAMETERS;
                 break;
    }
    return rc;
}
