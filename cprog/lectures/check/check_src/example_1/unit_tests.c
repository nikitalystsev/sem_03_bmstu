#include <stdio.h>
#include <math.h>
#include "avg.h"


#define EPS     1.0e-7


// Тестовый сценарий для функции calc_avg
void test_calc_avg(void)
{
    int err_cnt = 0;

    // Тестовый сценарий состоит из тестовых случаев

    //
    // Неверные параметры
    //

    {
        int a[] = {1, 2, 3};
        double avg;

        if (calc_avg(NULL, 2, &avg) != ERR_INVALID_PARAM)
            err_cnt++;

        if (calc_avg(a, -3, &avg) != ERR_INVALID_PARAM)
            err_cnt++;

        if (calc_avg(a, sizeof(a) / sizeof(a[0]), NULL) != ERR_INVALID_PARAM)
            err_cnt++;
    }

    //
    // Пустой массив
    //

    {
        int a[] = {1, 2, 3};
        double avg;

        if (calc_avg(a, 0, &avg) != ERR_NO_DATA)
            err_cnt++;
    }

    //
    // Разные корректные массивы
    //

    {
        int a[] = {5, 2, -3, -4, 0};
        int b[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int c[] = {157};
        double avg;

        if (calc_avg(a, sizeof(a) / sizeof(a[0]), &avg) != OK || avg > EPS)
            err_cnt++;

        if (calc_avg(b, sizeof(b) / sizeof(b[0]), &avg) != OK || fabs(5 - avg) > EPS)
            err_cnt++;

        if (calc_avg(c, sizeof(c) / sizeof(c[0]), &avg) != OK || fabs(157 - avg) > EPS)
            err_cnt++;
    }

    printf("%s: %s\n", __func__, err_cnt ? "FAILED" : "OK");
}


int main(void)
{
    test_calc_avg();

    return 0;
}