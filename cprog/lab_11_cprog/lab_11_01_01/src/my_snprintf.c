#include "my_snprintf.h"

static int add_char(char *s, const char symbol, int index,
const int n, int *count)
{
    if (index < n - 1)
        s[index] = symbol, index++;

    (*count)++;

    return index;
}

static void reverse(char *s, const int len)
{
    for (size_t i = 0, j = len - 1; i < j; i++, j--)
    {
        char c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static size_t num_to_str(char *s, long num, const size_t radix)
{
    size_t len = 0;

    bool isneg = false;

    if (radix == RADIX_8 || radix == RADIX_16)
        num = (unsigned)num;

    if (!num)
    {
        s[len++] = '0';
        s[len] = '\0';
        return len;
    }

    if (num < 0 && radix == RADIX_10)
    {
        isneg = true;
        num = -num;
    }

    while (num)
    {
        int rem = num % radix;
        s[len++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= radix;
    }

    if (isneg)
        s[len++] = '-';

    s[len] = '\0';

    reverse(s, len);

    return len;
}

static int add_num(char *s, const long long num,
int index, const size_t radix, const int n, int *count)
{
    char str_num[MAX_LEN_NUM];

    size_t len = num_to_str(str_num, num, radix);

    for (size_t i = 0; i < len; i++)
        index = add_char(s, str_num[i], index, n, count);

    return index;
}

static int add_str(char *s, char *str, int index, const int n, int *count)
{
    for (size_t i = 0; i < strlen(str); i++)
        index = add_char(s, str[i], index, n, count);

    return index;
}

static int add_short(char *s, short num,
int index, const size_t n, int *count)
{
    char str_num[MAX_LEN_NUM];

    size_t len = num_to_str(str_num, num, RADIX_10);

    for (size_t i = 0; i < len; i++)
        index = add_char(s, str_num[i], index, n, count);

    return index;
}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
    if (n > INT_MAX)
        return ERR_LEN;

    int ind_str = 0, count = 0;

    va_list args;
    va_start(args, format);

    for (size_t i = 0; i < strlen(format); i++)
        if (format[i] == '%')
        {
            if (format[i + 1] == 'h' && format[i + 2] == 'i')
                ind_str = add_short(s, va_arg(args, int), ind_str, n, &count), i++;
            else if (format[i + 1] == 'l' && (format[i + 2] == 'i' || format[i + 2] == 'd'))
                ind_str = add_num(s, va_arg(args, long), ind_str, RADIX_10, n, &count), i++;
            else if (format[i + 1] == 'l' && format[i + 2] == 'l' &&
                (format[i + 3] == 'i' || format[i + 3] == 'd'))
                ind_str = add_num(s, va_arg(args, long long), ind_str, RADIX_10, n, &count), i += 2;
            else if (format[i + 1] == 'c')
                ind_str = add_char(s, va_arg(args, int), ind_str, n, &count);
            else if (format[i + 1] == 'd' || format[i + 1] == 'i')
                ind_str = add_num(s, va_arg(args, signed), ind_str, RADIX_10, n, &count);
            else if (format[i + 1] == 'x')
                ind_str = add_num(s, va_arg(args, unsigned), ind_str, RADIX_16, n, &count);
            else if (format[i + 1] == 'o')
                ind_str = add_num(s, va_arg(args, unsigned), ind_str, RADIX_8, n, &count);
            else if (format[i + 1] == 's')
                ind_str = add_str(s, va_arg(args, char *), ind_str, n, &count);

            i++;
        }
        else
            ind_str = add_char(s, format[i], ind_str, n, &count);

    va_end(args);

    if (s)
    {
        if ((size_t)ind_str > n - 1)
            s[n - 1] = '\0';
        else
            s[ind_str] = '\0';
    }

    return count;
}
