#include "timing.h"

// Получение времени в миллисекундах
long double microseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;

    // return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
    return val.tv_sec * 1000000ULL + val.tv_usec;
}