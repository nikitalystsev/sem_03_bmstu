/*
Слайд 8
*/

#include <stdio.h>

void print_ch(int n, ...)
{
    int i;
    int *p_i = &n;
    char *p_c = (char*) (p_i + 1);

    for (i = 0; i < n; i++, p_c++)
        printf("%c %d\n", *p_c, (int) *p_c);
}

int main(void)
{
    char c = 'c';

    print_ch(5, 'a', 'b', c, 'd', 'e');

    return 0;
}
