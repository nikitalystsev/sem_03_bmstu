#include "print_write_numbers.h"

int print_numbers(char const *argv)
{
    FILE *f = fopen(argv, "rb");
    int check = 0;
    if (f != NULL)
    {
        int num;
        int pos = 0;
        int rc = 0;
        while (get_number_by_pos(f, pos, &num) == 0)
        {
            rc += printf("%d ", num);
            pos += SIZE_INT;
        }
        if (rc == 0)
            check = ERR_NO_NUMBERS_IN_FILE;
        fclose(f);
    }
    else
        check = ERR_OPEN_FILE;

    return check;
}

int write_random_numbers_to_file(char const *argv[])
{
    FILE *f = fopen(argv[3], "wb");
    int check = 0;
    if (f != NULL)
    {
        int numbers;
        if ((numbers = atoi(argv[2])) != 0)
        {
            srand(time(NULL));
            for (int i = 0; i < numbers; i++)
            {
                int elem = rand() % 1000; // числа меньше 1000
                fwrite(&elem, SIZE_INT, 1, f);
            }
        }
        else
            check = ERR_NO_NUMBER;
        fclose(f);
    }
    else 
        check = ERR_OPEN_FILE;

    return check;
}
