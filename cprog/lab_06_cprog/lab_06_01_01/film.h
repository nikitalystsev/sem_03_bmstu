#ifndef __FILM_H__
#define __FILM_H__

#include "defines.h"
#include "read.h"
#include "check_string.h"
#include "cmp.h"

typedef struct
{
    char movie_title[NAME_SIZE];
    char directors_name[NAME_SIZE];
    int release_year;
} film_t;

#define SIZE sizeof(film_t)

#define BIN_SEARCH(key, field, cmp)                     \
    while (low <= high)                                 \
    {                                                   \
        middle = (low + high) / 2;                      \
        if (cmp(key, arr_films[middle].field) < 0)      \
            high = middle - 1;                          \
        else if (cmp(key, arr_films[middle].field) > 0) \
            low = middle + 1;                           \
        else                                            \
            return middle;                              \
    }

#define SORT(field, cmp)                                              \
    do                                                                \
    {                                                                 \
        for (int i = 0; i < count_films - 1; i++)                     \
            for (int j = 0; j < count_films - 1 - i; j++)             \
                if (cmp(films[j].field, films[j + 1].field) > 0)      \
                    swap(&films[j], &films[j + 1], sizeof(films[j])); \
    } while (0)

int binary_search(const char *const field,
const char *const key,
const film_t *const arr_films,
const int count_films,
cmp_int_t comparator_int,
cmp_str_t comparator_str);

void print_find_film(film_t *const arr_films, int rc);

int init_arr_films_from_file(FILE *file,
const char *const file_name,
film_t *const arr_films,
size_t *const count_films);

void print_film(const film_t *const film);

void print_arr_films(const film_t *const arr_films,
int count_films);

int read_film(FILE *const file, film_t *const film);

int sort_films_by_field(const char *const field,
film_t *const films,
const int count_films,
cmp_int_t cmp_int,
cmp_str_t cmp_str);

#endif
