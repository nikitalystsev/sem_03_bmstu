#include "gen_data.h"

void gen_data_file(const char *const file_name, const int count_data)
{
    srand(time(NULL));

    FILE *file = fopen(file_name, "w");

    fprintf(file, "%d\n", count_data);

    for (int i = 0; i < count_data; i++)
    {
        int x = MIN_DATA + rand() % (MAX_DATA - MIN_DATA + 1);

        fprintf(file, "%d\n", x);
    }

    fclose(file);
}
