// ВНИМАНИЕ
// Пример содержит ОШИБКУ

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p;

    p = malloc(sizeof(int));
    if (p)
    {
        *p = 5;
        
        printf("%d\n", *p);
        
        free(p);
        
        *p = 7;
        
        printf("%d\n", *p);
    }
    
    return 0;
}
