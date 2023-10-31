#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN_STRING 256
#define MAX_LEN_WORD 16

#define ERR_INPUT_STR 1
#define ERR_ALL_STR_ISSPACE 2
#define ERR_LEN_WORD 3
#define ERR_EMPTY_STRING 4
#define ERR_NULL_POINTER 5


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
    if (rc == NULL || strlen(string) > MAX_LEN_STRING 
        || check_string(string) == ERR_ALL_STR_ISSPACE)
        return ERR_INPUT_STR;
    return EXIT_SUCCESS;
}

int split_string(char (*const array_words)[MAX_LEN_STRING + 1], 
int *const n, char *const string)
{
    if (array_words == NULL || n == NULL || string == NULL)
        return ERR_NULL_POINTER;

    char *p = strtok(string, " ,;:-.!?");

    while (p != NULL)
    {
        strncpy(array_words[*n], p, MAX_LEN_STRING);
        array_words[*n][MAX_LEN_STRING] = '\0';
        for (int i = 0; i < *n; i++)
            if (strlen(array_words[*n]) > MAX_LEN_WORD)
                return ERR_LEN_WORD;
        (*n)++;
        p = strtok(NULL, " ,;:-.!?\n");
    }
    return EXIT_SUCCESS;
}
int shift(char *const word, size_t *const i, size_t *const n)
{
    if (word == NULL || i == NULL || n == NULL)
        return ERR_NULL_POINTER;

    size_t j = *i;
    for (; j < *n - 1; j++)
        word[j] = word[j + 1];
    word[j] = '\0';
    (*n)--;
    (*i)--;
    return EXIT_SUCCESS;
}

int del_next_occur_first_letter(char *const word, size_t n)
{
    if (word == NULL)
        return ERR_NULL_POINTER;

    char first_letter = word[0];

    for (size_t i = 1; i < n; i++)
        if (word[i] == first_letter)
            shift(word, &i, &n);
    return EXIT_SUCCESS;
}

int add_space(char *const string)
{
    if (string == NULL)
        return ERR_NULL_POINTER;
    
    strcat(string, " ");
    return EXIT_SUCCESS;
}

int create_new_string(char (*const array_words)[MAX_LEN_STRING + 1], 
int n, char *const new_string)
{
    if (array_words == NULL || new_string == NULL)
        return ERR_NULL_POINTER;

    const char *const last_word = array_words[n - 1];

    for (int i = n - 2; i >= 0; i--)
        if (strcmp(array_words[i], last_word) != 0)
        {
            del_next_occur_first_letter(array_words[i], strlen(array_words[i]));
            if (i == n - 2)
                strcat(new_string, array_words[i]);
            else if (i < n - 2 || i >= 0)
            {
                add_space(new_string);
                strcat(new_string, array_words[i]);
            } 
        }
    return EXIT_SUCCESS;
}

int main(void)
{
    char array_words[MAX_LEN_STRING + 1][MAX_LEN_STRING + 1] = { "" };
    
    char string[MAX_LEN_STRING + 1] = "";
    char new_string[MAX_LEN_STRING + 1] = "";

    int n = 0;

    int rc;
    if ((rc = input_string(string)) != EXIT_SUCCESS)
        return rc;

    if ((rc = split_string(array_words, &n, string)) != EXIT_SUCCESS)
        return rc;

    if ((rc = create_new_string(array_words, n, new_string)) != EXIT_SUCCESS)
        return rc;

    if (strlen(new_string) == 0)
        return ERR_EMPTY_STRING;

    printf("Result: %s\n", new_string);
    return EXIT_SUCCESS;
}
