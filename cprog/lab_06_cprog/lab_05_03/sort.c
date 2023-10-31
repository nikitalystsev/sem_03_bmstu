#include "sort.h"

void swap(FILE *f, int number1, int number2, int pos_1, int pos_2)
{
    put_number_by_pos(f, pos_1, &number2);
    put_number_by_pos(f, pos_2, &number1);
}

int sort_numbers_in_file(FILE *f)
{
    int pos_last_number;
    get_pos_last_number(f, &pos_last_number);

    fseek(f, pos_last_number, SEEK_SET);
    int last_number;

    if (fread(&last_number, SIZE_INT, 1, f) != 1)
        return ERR_NO_NUMBERS_IN_FILE;

    for (int pos1 = 0; pos1 <= pos_last_number - SIZE_INT; pos1 = pos1 + SIZE_INT)
    {
        for (int pos2 = 0; pos2 <= pos_last_number - SIZE_INT - pos1; pos2 = pos2 + SIZE_INT)
        {
            int number1;
            get_number_by_pos(f, pos2, &number1);
            int number2;
            get_number_by_pos(f, pos2 + SIZE_INT, &number2);

            if (number1 > number2)
                swap(f, number1, number2, pos2, pos2 + SIZE_INT);
        }
    }
    return EXIT_SUCCESS; 
}

int sort(char const *argv)
{
    FILE *f = fopen(argv, "rb+");
    int check = 0;
    if (f != NULL)
    {
        int rc;
        if ((rc = sort_numbers_in_file(f)) != 0)
            check = rc;
        fclose(f);
    }
    else
        check = ERR_OPEN_FILE;
    return check;
}
