// ВНИМАНИЕ
// Пример содержит ОШИБКУ

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n_elems = 5;
    int *arr = NULL;
    
    arr = malloc(n_elems);
    if (arr)
    {
        for (int i = 0; i < n_elems; i++)
            arr[i] = i;
        
        for (int i = 0; i < n_elems; i++)
            printf("%d ", arr[i]);
        
        free(arr);
    }
    
    return 0;
}
