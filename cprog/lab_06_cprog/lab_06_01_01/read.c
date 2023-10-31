#include "read.h"

int read_str(FILE *const file, char *const string)
{
    char *rc_str = fgets(string, NAME_SIZE + 1, file);
    if (rc_str == NULL || check_string(string) != 0)
        return ERR_CHECK_STR;
    return EXIT_SUCCESS;
}

int read_number(FILE *const file, int *const number)
{
    if (fscanf(file, "%d\n", number) != 1)
        return ERR_READ_NUM;
    if (*number <= 0)
        return ERR_NO_VALID_YEAR;
    return EXIT_SUCCESS;
}
