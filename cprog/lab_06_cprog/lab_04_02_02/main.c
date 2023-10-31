#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN_STRING 256
#define MAX_LEN_WORD 16

#define ERR_INPUT_STR 1
#define ERR_ALL_STR_ISSPACE 2
#define ERR_LEN_WORD 3
#define ERR_NULL_POINTER 4

int check_string(const char *const string)
{
    if (string == NULL)
        return ERR_NULL_POINTER;
    
    size_t count = 0;
    for (const char *ptr_string = string; *ptr_string != '\0'; ptr_string++)
        if (ispunct(*ptr_string) || isspace(*ptr_string))
            count++;
    if (strlen(string) == count)
        return ERR_ALL_STR_ISSPACE;
    return EXIT_SUCCESS;
}

int input_string(char *const string)
{
    if (string == NULL)
        return ERR_NULL_POINTER;

    char *rc = fgets(string, MAX_LEN_STRING + 2, stdin);
    if (rc == NULL || strlen(string) > MAX_LEN_STRING \
        || check_string(string) == ERR_ALL_STR_ISSPACE)
        return ERR_INPUT_STR;
    return EXIT_SUCCESS;
}

int write_symbol(char *const elem, const char *const symbol, 
int *const check_record, int *const count)
{
    if (check_record == NULL || count == NULL || elem == NULL || symbol == NULL)
        return ERR_NULL_POINTER;

    if (*symbol != '\n')
    {
        *elem = *symbol;
        *check_record = 1;
        (*count)++;
    }
    return EXIT_SUCCESS;
}

int split_string(char (*const array_words)[MAX_LEN_STRING + 1], size_t *n, 
const char *const string)
{  
    if (string == NULL || n == NULL || array_words == NULL)
        return ERR_NULL_POINTER;

    int j = 0;
    int check_record = 0;
    for (const char *ptr_string = string; *ptr_string != '\0'; ptr_string++)
    {
        if (ispunct(*ptr_string) || isspace(*ptr_string))
        {
            array_words[*n][j] = '\0';
            if (strlen(array_words[*n]) > MAX_LEN_WORD)
                return ERR_LEN_WORD;
            if (check_record == 1)
                (*n)++;

            check_record = 0; 
            j = 0;
            continue;
        }
        if (write_symbol(&array_words[*n][j], ptr_string, &check_record, &j) == ERR_NULL_POINTER)
            return ERR_NULL_POINTER;
    }
    if (check_record)
        (*n)++;

    return EXIT_SUCCESS;
}

int print_result(char (*const array_words1)[MAX_LEN_STRING + 1], const size_t *n1, 
char (*const array_words2)[MAX_LEN_STRING + 1], const size_t *n2)
{
    if (n1 == NULL || n2 == NULL || array_words2 == NULL || array_words1 == NULL)
        return ERR_NULL_POINTER;

    printf("Result: \n");
    for (size_t i = 0; i < *n1; i++)
    {
        int equal = 0;
        for (size_t j = 0; j < *n2; j++)
            if (strcmp(array_words1[i], array_words2[j]) == 0)
            {
                printf("%s yes\n", array_words1[i]);
                equal = 1;
                break;
            }
        if (equal == 0)
            printf("%s no\n", array_words1[i]); 
    }
    return EXIT_SUCCESS;
}

int delete_reccuring_elem(char (*const array_words)[MAX_LEN_STRING + 1], size_t *n)
{
    if (n == NULL || array_words == NULL)
        return ERR_NULL_POINTER;

    size_t distantion = 0;

    for (size_t i = 0; i < *n; i++)
    {
        int flag = 0;
        for (size_t j = 0; j < i; j++)
            if (strcmp(array_words[i], array_words[j]) == 0)
            {
                flag = 1;
                break;
            }
        if (flag)
            distantion++;
        else
        {
            if (distantion) 
            {
                strncpy(array_words[i - distantion], array_words[i], MAX_LEN_STRING);
                array_words[i - distantion][MAX_LEN_STRING] = '\0';
            }
        }
    }
    (*n) = (*n) - distantion;
    return EXIT_SUCCESS;
}

int main(void)
{
    size_t n1 = 0;
    size_t n2 = 0;

    char array_words1[MAX_LEN_STRING][MAX_LEN_STRING + 1] = { "" };
    char array_words2[MAX_LEN_STRING][MAX_LEN_STRING + 1] = { "" };
    char string1[MAX_LEN_STRING + 1] = "";
    char string2[MAX_LEN_STRING + 1] = "";

    int rc;
    if ((rc = input_string(string1)) != EXIT_SUCCESS)
        return rc;

    if ((rc = input_string(string2)) != EXIT_SUCCESS)
        return rc;

    if ((rc = split_string(array_words1, &n1, string1)) != EXIT_SUCCESS)
        return rc;

    if ((rc = split_string(array_words2, &n2, string2)) != EXIT_SUCCESS)
        return rc;

    if ((rc = delete_reccuring_elem(array_words1, &n1)) != EXIT_SUCCESS)
        return rc;

    if ((rc = print_result(array_words1, &n1, array_words2, &n2)) != EXIT_SUCCESS)
        return rc;

    return EXIT_SUCCESS;
}
