/*
Слайд 4
*/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    FILE *f;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    
    if (argc != 2)
    {
        printf("app.exe file_name\n");
        return 1;
    }
    
    f = fopen(argv[1], "r");
    if (f)
    {
        while ((read = getline(&line, &len, f)) != -1)
        {
            printf("len %d, read %d\n", (int) len, (int) read);
            printf("%s", line);
        }
        
        free(line);
        fclose(f);
    }

    return 0;
}
