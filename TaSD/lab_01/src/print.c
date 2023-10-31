#include "../inc/print.h"

void input_float(char *string, int num)
{
    printf(
        "                           1        10        20         31 E\n"
        "                          ±|........|.........|..........|..|...|\n"
        "Enter the real number №%d: ",
        num);

    fscanf(stdin, "%s", string);
    printf("\n");
}

void rules(void)
{
    printf("Division of a real number by a real number.\n"
           "A real number is represented as <+-m.nE+-K>,\n"
           "where the total length of the mantissa (m+n) is up to\n"
           "30 significant digits K order value up to 5 digits\n"
           "\n"
           "Rules for entering numbers:\n"
           "1 - The number must be preceded by its sign (+ or -).\n"
           "2 - There must be a sign (+ or -) before the order\n"
           "3 - The number is entered without spaces.\n"
           "4 - When entering a number in exponential notation,\n"
           "        the degree must be entered with a capital E.\n"
           "5 - The maximum length of a real number is 39 characters.\n"
           "        1 digit character, 30 mantissa characters,\n"
           "        1 dot character,1 degree character,\n"
           "        1 exponuent character, 5 exponent characters\n"
           "\n");
}

void print_number(const real_number_t *const real_number)
{
    print_array(real_number->mantissa, real_number->len_mantissa);
    printf("len mantissa = %d\n", real_number->len_mantissa);
    printf("power = %d\n", real_number->power);
    printf("sign_num: %c\n", real_number->sing_num);
    printf("point_pos: %d\n", real_number->point_pos);
    printf("e_pos: %d\n", real_number->e_pos);
}

void print_array(const int *const array, size_t n)
{
    printf("Array:\n");;

    for (size_t i = 0; i < n; i++)
        printf("%d", array[i]);

    printf("\n");
}

void print_result(const real_number_t *const result)
{
    printf("Result %c0.", result->sing_num);
    for (int i = 1; i < result->len_mantissa; i++)
        printf("%d", result->mantissa[i]);

    printf("E%+d", result->power);
}