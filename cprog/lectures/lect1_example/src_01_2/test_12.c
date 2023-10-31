// ВНИМАНИЕ
// Пример содержит ОШИБКУ

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n_elems = 5;
    int *pbeg, *pend;

    pbeg = malloc(n_elems * sizeof(int));
    if (pbeg)
    {
        pend = pbeg + n_elems;
        
        while (pbeg < pend)
        {
            *pbeg = 0;
            pbeg++;
        }
        
        free(pbeg);
    }
    
    return 0;
}
