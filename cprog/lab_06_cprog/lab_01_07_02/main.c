#include <stdio.h>
#include <math.h>
#define SUCCESS 0
#define ERROR 1
#define BIG_ARGUMENTS 2
#define ERROR_EPSILON 3
#define NO_CALC_SUM 4
#define CORRECT_INPUT 2

int check_input(double x, double e)
{
    if (fabs(x) > 1)
    {
        printf("Error: modulo x must not exceed one");
        return BIG_ARGUMENTS;
    }
    else if ((e <= 0) || (e > 1))
    {
        printf("Error: accuracy must be between zero and one");
        return ERROR_EPSILON;
    }
    else if (fabs(x) < e)
    {
        printf("Error: summa no calculate");
        return NO_CALC_SUM;
    }
    return SUCCESS;
}

double calc_arcsin(double x, double e)
{
    int n = 0;
    double row_member = x;
    double summa = 0;
    double part1;
    double part2;

    while (fabs(row_member) >= e)
    {
        summa += row_member;
        part1 = (2 * n + 1) * (2 * n + 1) * x * x;
        part2 = 2 * (2 * n + 3) * (n + 1);
        row_member *= (part1 / part2);
        n++;
    }
    return summa;
}

double count_abs_error(double exact_value, double approximation)
{
    double abs_error = fabs(exact_value - approximation);
    return abs_error;
}

double count_relative_error(double abs_error, double exact_value)
{
    double relative_error = abs_error / (fabs(exact_value));
    return relative_error;
}

int main(void)
{
    double x, e;
    int rc;
    double exact_value;
    double approximation;
    double abs_error, relative_error;

    puts("Enter function argument and precision:");
    rc = scanf("%lf", &x);
    rc += scanf("%lf", &e);

    if (rc != CORRECT_INPUT)
    {
        printf("Error: wrong input");
        return ERROR;
    }
 
    rc = check_input(x, e);
    if (rc == BIG_ARGUMENTS)
        return BIG_ARGUMENTS;
    else if (rc == ERROR_EPSILON)
        return ERROR_EPSILON;
    else if (rc == NO_CALC_SUM)
        return NO_CALC_SUM; 
   

    exact_value = asin(x);
    approximation = calc_arcsin(x, e);

    abs_error = count_abs_error(exact_value, approximation);
    relative_error = count_relative_error(abs_error, exact_value);

    printf("%lf %lf %lf %lf",
    approximation, exact_value, abs_error, relative_error);
    return SUCCESS;
}
