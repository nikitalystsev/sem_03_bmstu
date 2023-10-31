#include "process.h"

int process(FILE *f, int *const count_equal)
{   
    rewind(f);
    int number, next_number;

    if (fscanf(f, "%d", &number) != 1)
        return ERR_NO_NUMBERS;

    int curr_count = 1, max_count = 1;
    while (fscanf(f, "%d", &next_number) == 1)
    {
        if (number != next_number)
            curr_count = 1;
        else
        {
            curr_count++;
            max_count = max(curr_count, max_count); 
        }
        number = next_number;
    }
    *count_equal = max_count;
    
    return EXIT_SUCCESS;
}
