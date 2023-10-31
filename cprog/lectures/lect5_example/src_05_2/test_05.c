/*
Слайд 7
*/

//#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#define NAME "Igor"
#define CITY "Moscow"

int main(int argc, char **argv)
{
    char *line = NULL;
    int n;
    
    n = asprintf(&line, "My name is %s. I live in %s.", NAME, CITY);
    if (n > 0)
    {
        printf("n = %d\n", n);
        printf("%s\n", line);
        
        free(line);
    }
    
    return 0;
}
