#include "get_put_numbers.h"
#include "sort.h"
#include "print_write_numbers.h"
#include "defines.h"
#include "check_argc.h"

int main(int argc, char const *argv[])
{
    int mark = check_argc(argc, argv);
    int rc;
    switch (mark)
    {
        case 1: 
            rc = write_random_numbers_to_file(argv);
            break;
        case 2: 
            rc = print_numbers(argv[2]);
            break;
        case 3: 
            rc = sort(argv[2]);
            break;
        default:
            return ERR_NO_VALID_PARAMETERS;
    }
    if (rc != 0)
        return rc;

    return EXIT_SUCCESS;
}
