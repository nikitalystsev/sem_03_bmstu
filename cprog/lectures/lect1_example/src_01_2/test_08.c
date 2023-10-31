// ВНИМАНИЕ
// Пример содержит ОШИБКУ

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *p = NULL;
    
    p = malloc(sizeof(int));
    if (p)
    {
        *p = 5;
        
        printf("%d\n", *p);
        
        p = malloc(sizeof(int));
        if (p)
        {
            *p = 10;
            
            printf("%d\n", *p);
        }
        
        free(p);
    }
    
    return 0;
}
