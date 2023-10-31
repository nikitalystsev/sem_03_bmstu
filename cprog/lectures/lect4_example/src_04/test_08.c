#define N 3
#define M 2

void foo_2(int **a, size_t n, size_t m)
{
}

int main(void)
{
    int a[N][M];
    size_t n = N, m = M;
    int* b[N] = {a[0], a[1], a[2]};

    /*
    // Такой вызов не откомпилируется    
    foo_2(a, n, m);
    */
	
    // А такой откомпилируется
    foo_2(b, n, m);

    return 0;    
}