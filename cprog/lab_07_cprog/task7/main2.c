// c99
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#ifndef NMAX 
#error  where?
#endif
#define N_REPS    1

#define ERR_WRONG_INPUT 1
#define ERR_WRONG_DIMENSION 2
#define ERR_EXPR_NO_CALC 3
#define SUCCESS 0

// Получение времени в миллисекундах
unsigned long long milliseconds_now(void)
{
    struct timeval val;

    if (gettimeofday(&val, NULL))
        return (unsigned long long) -1;

    return val.tv_sec * 1000ULL + val.tv_usec / 1000ULL;
}

int compare(const void *value1, const void *value2)
{
    return (*(int *)value1 - *(int *)value2); 
}

int main(void)
{
    int a[NMAX];
    size_t n = sizeof(a) / sizeof(a[0]);
    long long unsigned beg, end;

    srand(time(NULL));
    
    for (size_t i = 0; i < n; i++)
        a[i] = rand();
    

    beg = milliseconds_now();
    qsort(a, n, sizeof(int), compare);
    end = milliseconds_now();

    printf("%g\n", (double) (end - beg));

    return SUCCESS;
}