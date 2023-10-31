#include "check_string.h"

int check_year(const char *const string, int *const year)
{
    *year = atoi(string);

    if (*year <= 0)
        return ERR_NO_VALID_YEAR;

    return EXIT_SUCCESS;
}

bool isspace_string(const char *const string)
{
    for (size_t i = 0; i < strlen(string); i++)
        if (!(isspace(string[i]) && ispunct(string[i])))
            return false;

    return true;
}

int check_string(char *const string)
{
    size_t len = strlen(string);
    
    if (len == NAME_SIZE && string[len - 1] != '\n')
        return ERR_CHECK_STR;

    if (len <= NAME_SIZE && string[len - 1] == '\n')
        string[len - 1] = '\0';

    if (strlen(string) == 0 || isspace_string(string))
        return ERR_CHECK_STR;

    return EXIT_SUCCESS;
}
