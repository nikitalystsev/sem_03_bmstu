#include <stdlib.h>

#define N 5
#define M 4

// В комментарии подсказка!
void foo_1(int a[][M] /*int (*a)[M]*/, size_t n, size_t m)
{
}

int main(void)
{
    int a[N][M];        // статический массив
    int *b = NULL;      // матрица как одномерный массив
    int **c = NULL;     // матрица как массив указателей
    size_t n = N, m = M;

    foo_1(a, n, m);     // откомпилируется?
    foo_1(b, n, m);     // откомпилируется?
    foo_1(c, n, m);     // откомпилируется?

    return 0;  
}