#include "functions.h"

int find_average_between_max_min(FILE *const f, double *const average,
const int begin_ind, const int end_ind)
{
    fseek(f, 0, SEEK_SET);

    int curr_index = 0;
    int count_number = 0;
    double number;
    double sum = 0;

    while (fscanf(f, "%lf", &number) == 1)
    {   
        if (curr_index > begin_ind && curr_index < end_ind)
        {
            sum += number;
            count_number++;
        }
        curr_index++;
    }
    if (count_number == 0)
        return ERR_NO_AVERAGE_BETWEEN_MIN_MAX;

    *average = sum / count_number;

    return EXIT_SUCCESS;
}

int find_max_min_in_file(FILE *const f, int *const ind_max, int *const ind_min)
{
    double max;

    if (fscanf(f, "%lf", &max) != 1)
        return ERR_FIRST_ELEM_NO_NUMBER;
    double min = max;

    int curr_index = 0;
    double number;
    while (fscanf(f, "%lf", &number) == 1)
    {   
        curr_index++;
        if (number > max)
        {
            max = number;
            *ind_max = curr_index;
        }
        if (number < min)
        {
            min = number;
            *ind_min = curr_index;
        }
    }
    return EXIT_SUCCESS;
}

void definition_begin_end_indexes(int *const ind_1, int *const ind_2)
{
    if (*ind_1 > *ind_2)
    {
        int tmp = *ind_1;
        *ind_1 = *ind_2;
        *ind_2 = tmp;
    }
}
