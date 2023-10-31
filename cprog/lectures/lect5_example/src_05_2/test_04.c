/*
Слайд 6
*/

#include <stdio.h>
#include <stdlib.h>

#define NAME "Igor"
#define CITY "Moscow"

int main(int argc, char **argv)
{
    int n, m;
    
    n = snprintf(NULL, 0, "My name is %s. I live in %s.", NAME, CITY);
    if (n > 0)
    {
        char *line = malloc((n + 1) * sizeof(char));
        if (line)
        {
            m = snprintf(line, n + 1, "My name is %s. I live in %s.", NAME, CITY);
            
            printf("n = %d, m = %d\n", n, m);
            printf("%s\n", line);
            
            free(line);
        }
    }
    
    return 0;
}