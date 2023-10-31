#include <string.h>
#include "example.h"

EXAMPLE_DLL int EXAMPLE_DECL add(int a, int b)
{
    return a + b;
}


EXAMPLE_DLL int EXAMPLE_DECL divide(int a, int b, int *remainder)
{
    int quot = a / b;
	
    *remainder = a % b;
	
    return quot;
}


EXAMPLE_DLL double EXAMPLE_DECL avg(double *arr, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += arr[i];

    return sum / n;
}


EXAMPLE_DLL void EXAMPLE_DECL fill_array(double *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}


EXAMPLE_DLL int EXAMPLE_DECL filter(double *src, int src_len, double *dst, int *dst_len)
{
    int n;

    n = 0;
    for (int i = 0; i < src_len; i++)
        if (src[i] < 0)
            n++;

    if (n > *dst_len)
    {
        *dst_len = n;

        return 1;
    }

    n = 0;
    for (int i = 0; i < src_len; i++)
        if (src[i] < 0)
        {
            dst[n] = src[i];
            n++;
        }

    *dst_len = n;

    return 0;
}
