#include <stdio.h>
#include <stdlib.h>

#define ERR_OK		0
#define ERR_IO		1
#define ERR_MEM		2
#define ERR_ARGS	3
#define ERR_NO_DATA	4

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

int create_array(FILE *f, int **arr, size_t *n)
{
    int *p = NULL;
    int rc = 0;

    *n = get_count(f);
    if (*n)
    {
        p = malloc(*n * sizeof(int));
        if (p)
        {
            rewind(f);
            
            rc = read_array(f, p, *n);
            if (rc == ERR_OK)
            {
                *arr = p;
            }
            else
            {
                free(p);
                p = NULL;
            }
        }
        else
            rc = ERR_MEM;
    }
    else
        rc = ERR_NO_DATA;
    
    return rc;
}

int create_array_2(FILE *f, int **arr, int *n)
{
    int rc = 0;

    *n = get_count(f);
    if (*n)
    {
        *arr = malloc(*n * sizeof(int));
        if (*arr)
        {
            rewind(f);
            
            rc = read_array(f, *arr, *n);
        }
        else
            rc = ERR_MEM;
    }
    else
        rc = ERR_NO_DATA;
    
    return rc;
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
        rc = create_array(f, &arr, &n);
        if (rc == ERR_OK)
        {
			// Работа с массивом
            print_array(arr, n);
            
            free(arr);
        }
    
        fclose(f);
    }
    else
        rc = ERR_IO;

    return rc;
}
