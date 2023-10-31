/*
Слайд 3
*/

// Для компиляции -std=gnu99

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME "Bauman Moscow State Technical University"

int main(void)
{
    char *name = strdup(NAME);    // string.h, POSIX (strndup)
    
    if (name)
    {
        printf("%s\n", name);
        
        free(name);
    }
    else
        printf("Cant allocate memory\n");

    return 0;
}
