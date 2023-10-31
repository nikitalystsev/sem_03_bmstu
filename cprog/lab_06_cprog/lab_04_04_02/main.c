#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_LEN_STRING 256
#define MAX_LEN_WORD 16
#define COUNT_WORDS 3
#define COUNT_MONTHS 12

#define ERR_INPUT_STR 1
#define ERR_LEN_WORD 2
#define ERR_EMPTY_STRING 3
#define ERR_NULL_POINTER 4

#define NO_VALID_DAY 5
#define NO_VALID_MONTH 6
#define NO_VALID_YEAR 7
#define NO_VALID_DATA 8

int input_string(char *const s)
{
    if (s == NULL)
        return ERR_NULL_POINTER;

    char *rc = fgets(s, MAX_LEN_STRING + 2, stdin);
    if (rc == NULL || strlen(s) > MAX_LEN_STRING)
        return ERR_INPUT_STR;
    return EXIT_SUCCESS;
}

int check_day(const char *const word, int *const day)
{
    if (word == NULL || day == NULL)
        return ERR_NULL_POINTER;

    size_t len = strlen(word);
    size_t count = 0;
    for (size_t i = 0; i < len; i++)
        if (isdigit(word[i]) != 0)
            count++;

    int numb = atoi(word);
    if (numb != 0)
        *day = numb;

    if (count != len || numb == 0)
        return NO_VALID_DAY;

    return EXIT_SUCCESS;
}

int check_month(const char *const word, int *const month)
{
    if (word == NULL || month == NULL)
        return ERR_NULL_POINTER;

    *month = 0;
    size_t len = strlen(word);
    size_t count = 0;
    for (size_t i = 0; i < len; i++)
        if (isalpha(word[i]) != 0)
            count++;

    char lower_month[][10] = 
    { 
        "january", 
        "february", 
        "march", 
        "april", 
        "may", 
        "june", 
        "july", 
        "august", 
        "september", 
        "october", 
        "november", 
        "december"
    };
    for (size_t i = 0; i < COUNT_MONTHS; i++)
    {
        size_t count = 0;   // длина слова
        size_t j = 0;

        for (size_t k = 0; k < len; k++, j++)
            if (word[k] == lower_month[i][j] || word[k] == toupper(lower_month[i][j]))
                count++;

        if (count == strlen(lower_month[i]) && count == len)
            *month = i + 1;
    }

    if (count != len || *month == 0)
        return NO_VALID_MONTH;

    return EXIT_SUCCESS;
}

int check_year(const char *const word, int *const year)
{
    if (word == NULL || year == NULL)
        return ERR_NULL_POINTER;

    size_t len = strlen(word);
    size_t count = 0;
    for (size_t i = 0; i < len; i++)
        if (isdigit(word[i]) != 0)
            count++;

    int numb = atoi(word);
    if (numb != 0)
        *year = numb;

    if (count != len || numb == 0)
        return NO_VALID_YEAR;

    return EXIT_SUCCESS;
}

int check_valid_data(const int day, const int month, const int year)
{
    if (month == 4 || month == 6 || month == 9 || month == 11)
        if (day > 30 || day < 1)
            return NO_VALID_DATA;

    if (month == 2)
    {
        if ((year & 3) == 0 && ((year % 25) != 0 || (year & 15) == 0))
        {
            if (day > 29 || day < 1)
                return NO_VALID_DATA;
        }
        else
        {
            if (day > 28 || day < 1)
                return NO_VALID_DATA;
        }
    }
    if (day > 31 || day < 1 || year <= 0)
        return NO_VALID_DATA;
    return EXIT_SUCCESS;
}

int check_date(const char *const str_day, 
const char *const str_month, const char *const str_year)
{
    if (str_day == NULL || str_month == NULL || str_year == NULL)
        return ERR_NULL_POINTER;

    int day = 0, month = 0, year = 0;
    int rc = check_day(str_day, &day);
    rc += check_month(str_month, &month);
    rc += check_year(str_year, &year);
    rc += check_valid_data(day, month, year);
    if (rc != 0)
        return NO_VALID_DATA;
    
    return EXIT_SUCCESS;
}



int split_string(char (*const array_words)[MAX_LEN_STRING + 1],
int *const n, char *const string)
{
    if (array_words == NULL || n == NULL || string == NULL)
        return ERR_NULL_POINTER;

    char *p = strtok(string, " \t\n\r\v\f");

    while (p != NULL)
    {
        strncpy(array_words[*n], p, MAX_LEN_STRING);
        array_words[*n][MAX_LEN_STRING] = '\0';
        if (strlen(array_words[*n]) > MAX_LEN_WORD)
            return ERR_LEN_WORD;
        (*n)++;
        p = strtok(NULL, " \t\n\r\v\f");
    }
    return EXIT_SUCCESS;
}

int main(void)
{
    char string[MAX_LEN_STRING + 1] = "";
    char array_words[MAX_LEN_STRING][MAX_LEN_STRING + 1] = { "" };

    int n = 0;
    int rc;
    if ((rc = input_string(string)) != EXIT_SUCCESS)
        return rc;

    rc = split_string(array_words, &n, string);
    if (n != COUNT_WORDS)
    {
        printf("NO\n");
        return EXIT_SUCCESS;
    }

    if ((rc += check_date(array_words[0], array_words[1], array_words[2])) == EXIT_SUCCESS)
    {
        printf("YES\n");
        return EXIT_SUCCESS;
    }
    printf("NO\n");
    return EXIT_SUCCESS;
}