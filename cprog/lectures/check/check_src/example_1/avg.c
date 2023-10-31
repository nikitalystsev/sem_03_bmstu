#include <stdlib.h>
#include "avg.h"


int calc_avg(const int *a, int n, double *avg)
{
    double sum = 0;

    if (a == NULL || n < 0 || avg == NULL)
        return ERR_INVALID_PARAM;

    if (n == 0)
        return ERR_NO_DATA;

    for (int i = 0; i < n; i++)
        sum += a[i];

    *avg = sum / n;

    return OK;
}
