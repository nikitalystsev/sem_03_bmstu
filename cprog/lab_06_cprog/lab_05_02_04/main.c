#include "functions.h"
#include "check_argc.h"

int main(int argc, char const *argv[])
{
    FILE *f;
    double average;
    int begin_ind = 0, end_ind = 0;
    int rc;

    if ((rc = check_count_argc(argc)) != 0)
        return rc;

    f = fopen(argv[1], "r");
    if (f != NULL)
    {
        find_max_min_in_file(f, &begin_ind, &end_ind);
        definition_begin_end_indexes(&begin_ind, &end_ind);
        rc = find_average_between_max_min(f, &average, begin_ind, end_ind);
        fclose(f);

        if (rc != 0)
            return rc;
    }
    else
        return ERR_OPEN_FILE;

    printf("%lf\n", average);

    return EXIT_SUCCESS;
}
