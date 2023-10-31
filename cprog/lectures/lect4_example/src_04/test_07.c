#include <stdlib.h>

#define N 5
#define M 4

void foo_3(int *a, size_t n, size_t m)
{
}

int main(void)
{
    int a[N][M];        // статический массив
    int *b = NULL;      // матрица как одномерный массив
    int **c = NULL;     // матрица как массив указателей
    size_t n = N, m = M;

    foo_3(a, n, m);     // откомпилируется?
    foo_3(b, n, m);     // откомпилируется?
    foo_3(c, n, m);     // откомпилируется?

    return 0;  
}