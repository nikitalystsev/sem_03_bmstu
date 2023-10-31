// ВНИМАНИЕ
// Пример содержит ОШИБКУ

#include <stdio.h>
#include <stdlib.h>

#define ERR_OK  0
#define ERR_MEM 1

int process(int n)
{
    int *p = NULL;
    
    p = malloc(sizeof(int));
    if (p)
    {
        *p = n;
        
        printf("%d\n", *p);
        
        return ERR_OK;
    }
    else
    {
        return ERR_MEM;
    }
}

int main(void)
{
    int rc = process(5);
    
    return rc;
}
