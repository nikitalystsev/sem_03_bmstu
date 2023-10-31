#include "film.h"

int binary_search(const char *const field,
const char *const key,
const film_t *const arr_films,
const int count_films,
cmp_int_t comparator_int,
cmp_str_t comparator_str)
{
    if (strcmp(field, "title") != 0 &&
        strcmp(field, "name") != 0 &&
        strcmp(field, "year") != 0)
        return ERR_NO_VALID_FIELD;

    int low, high, middle;
    low = 0;
    high = count_films - 1;

    if (strcmp(field, "title") == 0)
        BIN_SEARCH(key, movie_title, comparator_str);

    if (strcmp(field, "name") == 0)
        BIN_SEARCH(key, directors_name, comparator_str);

    if (strcmp(field, "year") == 0)
    {
        int year, rc;

        if ((rc = check_year(key, &year)) != 0)
            return rc;

        BIN_SEARCH(year, release_year, comparator_int);
    }

    return NO_FIND_FILM;
}

void print_find_film(film_t *const arr_films, int rc)
{
    if (rc == NO_FIND_FILM)
        printf("Not found\n");
    else
        print_film(&arr_films[rc]);
}

int init_arr_films_from_file(FILE *file,
const char *const file_name,
film_t *const arr_films,
size_t *const count_films)
{
    int rc = 0;

    file = fopen(file_name, "r");

    if (file == NULL)
        return ERR_OPEN_FILE;

    for (int i = 0; !feof(file); i++)
    {
        if ((rc = read_film(file, &arr_films[i])) != 0)
            break;
        (*count_films)++;
        if (*count_films > MAX_COUNT_FILMS - 1)
        {
            rc = ERR_COUNT_FILMS;
            break;
        }
    }

    if (fclose(file) != 0)
        return ERR_CLOSE_FILE;

    if (*count_films == 0)
        return ERR_EMPTY_FILE;

    return rc;
}

void print_film(const film_t *const film)
{
    printf("%s\n%s\n%d\n", film->movie_title,
    film->directors_name, film->release_year);
}

void print_arr_films(const film_t *const arr_films,
int count_films)
{
    for (int i = 0; i < count_films; i++)
        print_film(&arr_films[i]);
}

int read_film(FILE *const file, film_t *const film)
{
    char string[NAME_SIZE + 1];
    int rc = 0;

    if ((rc = read_str(file, string)) != 0)
        return rc;
    strcpy(film->movie_title, string);

    if ((rc = read_str(file, string)) != 0)
        return rc;
    strcpy(film->directors_name, string);

    int number;

    if ((rc = read_number(file, &number)) != 0)
        return rc;
    film->release_year = number;

    return rc;
}

int sort_films_by_field(const char *const field,
film_t *const films,
const int count_films,
cmp_int_t cmp_int,
cmp_str_t cmp_str)
{
    if (strcmp(field, "title") == 0)
        SORT(movie_title, cmp_str);
    else if (strcmp(field, "name") == 0)
        SORT(directors_name, cmp_str);
    else if (strcmp(field, "year") == 0)
        SORT(release_year, cmp_int);
    else
        return ERR_NO_VALID_FIELD;

    return EXIT_SUCCESS;
}
