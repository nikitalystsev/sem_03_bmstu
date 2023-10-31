/*
Найти все пары слов, являющиеся палиндромами. Пример: hello, ollah
*/


#include <stdio.h>

#define NMAX 10
#define LEN_STR 6

void print_str(char words[NMAX][LEN_STR], int n)
{
    for (int i = 0; i < n; i++)
        printf("%s\n", words[i]);
}

void init_words(FILE *f, char words[NMAX][LEN_STR], int *n)
{
    while (fscanf(f, "%s", words[*n]) == 1)
        (*n)++;
}

int check_palindromes(char word1[LEN_STR], char word2[LEN_STR])
{
    int c = 0;
    for (int i = 0, j = LEN_STR - 2; i < LEN_STR - 1 && j >= 0; i++, j--)
    {
        if (word1[i] == word2[j])
            c++;
    }
    if  (c == LEN_STR - 1)
        return 0;
    else
        return 1;
}

void print_to_file(FILE *f_out, char word1[LEN_STR], char word2[LEN_STR])
{
    fprintf(f_out, "%s, ", word1);
    fprintf(f_out, "%s\n", word2);
}

void find_palindromes(FILE *f_out, char words[NMAX][LEN_STR], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (check_palindromes(words[i], words[j]) == 0)
            {
                print_to_file(f_out, words[i], words[j]);
            }
}

int main(int argc, char const *argv[])
{
    char words[NMAX][LEN_STR];
    if (argc == 3)
    {
        int n = 0;
        FILE *f = fopen(argv[1], "r");
        FILE *f_out = fopen(argv[2], "w");
        if (f != NULL && f_out != NULL)
        {
            init_words(f, words, &n);
            find_palindromes(f_out, words, n);
            fclose(f);
            fclose(f_out);
        }
    }
    return 0;
}