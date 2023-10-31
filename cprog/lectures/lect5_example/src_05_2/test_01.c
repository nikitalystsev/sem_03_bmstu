/*
Слайд 2
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME "Bauman Moscow State Technical University"

int main(void)
{
    char *name = malloc((strlen(NAME) + 1) * sizeof(char));
    
    if (name)
    {
        strcpy(name, NAME);
        
        printf("%s\n", name);
        
        free(name);
    }
    else
        printf("Cant allocate memory\n");

    return 0;
}