#include "find_substr.h"

int find_student_by_substr(student_t *arr_students, 
int count_students, char *substr, student_t *students, int *number_substr_std)
{
    size_t len = strlen(substr);
    int j = 0;
    for (int i = 0; i < count_students; i++)
    {
        if (strncmp(arr_students[i].last_name, substr, len) == 0)
        {
            students[j] = arr_students[i];
            (*number_substr_std)++;
            j++;
        }
    }
    if (*number_substr_std == 0)
        return ERR_NO_RECORD_DATA;
    return EXIT_SUCCESS;
}
