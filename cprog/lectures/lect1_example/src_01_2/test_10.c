// ВНИМАНИЕ
// Пример содержит ОШИБКУ

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p;

    setbuf(stdout, NULL);
    
    printf("Input n: ");
    if (scanf("%d", p) == 1)
    {
        printf("%d", *p);
    }
    
    return 0;
}
