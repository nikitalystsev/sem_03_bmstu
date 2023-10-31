#include <stdio.h>
#include <stdlib.h>

#define ERR_OK		0
#define ERR_IO		1
#define ERR_MEM		2
#define ERR_ARGS	3

size_t get_count(FILE *f)
{
    int dummy;
	size_t n = 0;

    while (fscanf(f, "%d", &dummy) == 1)
        n++;

    return n;
}

int read_array(FILE *f, int *arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
        if (fscanf(f, "%d", arr + i) != 1)
            return ERR_IO;

    return ERR_OK;
}

int* create_array(FILE *f, size_t *n)
{
    int *p = NULL;

    *n = get_count(f);
    if (*n)
    {
        p = malloc(*n * sizeof(int));
        if (p)
        {
            rewind(f);
            
            if (read_array(f, p, *n))
            {
                free(p);
                p = NULL;
            }
        }
    }
    
    return p;
}

void print_array(const int *arr, size_t n)
{
    printf("Array:\n");
    for (size_t i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(int argc, char **argv)
{
    FILE *f;
    int *arr = NULL;
    size_t n = 0;
    int rc;

    if (argc != 2)
    {
        printf("Usage\napp.exe file_name\n");

        return ERR_ARGS;
    }
    
    f = fopen(argv[1], "r");
    if (f)
    {
        arr = create_array(f, &n);
        if (arr)
        {
            // Работа с массивом
            print_array(arr, n);
			
            rc = ERR_OK;
            
            free(arr);
        }
        else
            // Тут толком не знаем, что произошло. Можно еще проанализовать значение n.
            rc = ERR_IO;
    
        fclose(f);
    }
    else
        rc = ERR_IO;

    return rc;
}
