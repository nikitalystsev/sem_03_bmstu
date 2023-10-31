#include "gen_data.h"

void gen_data_file(const char *file_name)
{
    srand(time(NULL));

    FILE *file = fopen(file_name, "w");

    fprintf(file, "%d\n", COUNT_DATA);

    for (int i = 0; i < COUNT_DATA; i++)
    {
        int x = MIN_DATA + rand() % (MAX_DATA - MIN_DATA + 1);

        fprintf(file, "%d\n", x);
    }

    fclose(file);
}
