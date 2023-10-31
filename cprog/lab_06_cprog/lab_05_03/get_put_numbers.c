#include "get_put_numbers.h"
#include "defines.h"

int put_number_by_pos(FILE *f, int pos, const int *const number)
{
    if (pos % SIZE_INT != 0)
    {
        printf("Error: no write by this position!\n");
        return ERR_NO_WRITE_POSITION;
    }

    fseek(f, pos, SEEK_SET);
    if (fwrite(number, SIZE_INT, 1, f) != 1)
        return END_OF_FILE;

    return EXIT_SUCCESS;
}

int get_number_by_pos(FILE *f, int pos, int *const number)
{
    if (pos % SIZE_INT != 0)
    {
        printf("Error: no read by this position!\n");
        return ERR_NO_READ_POSITION;
    }

    fseek(f, pos, SEEK_SET);
    if (fread(number, SIZE_INT, 1, f) != 1)
        return END_OF_FILE;

    return EXIT_SUCCESS;
}

int get_pos_last_number(FILE *f, int *const pos_last_number)
{
    fseek(f, 0, SEEK_SET);
    int pos = 0;
    int number = 0;
    while (get_number_by_pos(f, pos, &number) == 0)
    {
        *pos_last_number = pos;
        pos += SIZE_INT;
    }
    return EXIT_SUCCESS;
}
