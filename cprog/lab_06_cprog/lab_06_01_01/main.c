#include "film.h"
#include "read.h"
#include "cmp.h"

int main(int argc, char const *argv[])
{
    if (argc != PARAM_LIST && argc != PARAM_FIND)
        return ERR_WRONG_NUMBERS_OF_PARAM;

    film_t arr_films[MAX_COUNT_FILMS];
    size_t count_films = 0;

    FILE *file = NULL;
    int rc;

    if ((rc = init_arr_films_from_file(file, argv[1], arr_films, &count_films))
        != 0)
        return rc;

    if ((rc = sort_films_by_field(argv[2], arr_films, count_films, compare_int, compare_str)) != 0)
        return rc;

    if (argc == PARAM_LIST)
        print_arr_films(arr_films, count_films);

    if (argc == PARAM_FIND)
    {
        rc = binary_search(argv[2], argv[3], arr_films, count_films, compare_int, compare_str);

        if (rc == ERR_NO_VALID_YEAR || rc == ERR_NO_VALID_FIELD)
            return rc;
        print_find_film(arr_films, rc);
    }
    
    return EXIT_SUCCESS;
}
