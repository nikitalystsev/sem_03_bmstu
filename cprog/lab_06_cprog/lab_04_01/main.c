#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Эта функция находит первый символ в строке s1, 
который соответствует любому символу, указанному в s2 (она исключает завершение нулевых символов).
Он возвращает указатель на символ в s1, который
соответствует одному из символов в s2, иначе возвращает NULL.
*/
const char *my_strpbrk(const char *str1, const char *str2)
{	
    for (const char *ptr_str1 = str1; *ptr_str1 != '\0'; ptr_str1++)
        for (const char *ptr_str2 = str2; *ptr_str2 != '\0'; ptr_str2++)
            if (*ptr_str1 == *ptr_str2)
                return ptr_str1;
    return NULL;
}

/*
Функция strspn() возвращает длину начальной подстроки строки, 
на которую указывает str1, которая состоит только из тех символов, 
которые содержатся в строке, на которую указывает str2.
Эта функция
возвращает количество символов
в начальном сегменте str1 
которые состоят только из символов
из str2.
*/
size_t my_strspn(const char *str1, const char *str2)
{
    size_t len = 0;
    for (const char *ptr_str1 = str1; *ptr_str1 != '\0'; ptr_str1++)
    {
        int flag = 0;
        for (const char *ptr_str2 = str2; *ptr_str2 != '\0'; ptr_str2++)
            if (*ptr_str1 == *ptr_str2)
                flag = 1;
        if (!flag)
            return len;
        len++;
    }
    return len;
}

/*
Библиотечная функция C strcspn() 
вычисляет длину количества символов до 1-го вхождения символа, присутствующего в обеих строках.
Эта функция возвращает количество символов до 1-го вхождения
символа, присутствующего в обеих строках.
*/
size_t my_strcspn(const char *str1, const char *str2)
{
    size_t len = 0;
    for (const char *ptr_str1 = str1; *ptr_str1 != '\0'; ptr_str1++)
        len++;
    for (const char *ptr_str2 = str2; *ptr_str2 != '\0'; ptr_str2++)
    {
        size_t count_elem_before = 0;
        for (const char *ptr_str1 = str1; *ptr_str1 != '\0'; ptr_str1++)
        {
            count_elem_before++;
            if (*ptr_str2 == *ptr_str1)
                if (count_elem_before - 1 < len)
                    len = count_elem_before - 1;
        }
    }
    return len;
}

/*
Функция strchr выполняет поиск первого вхождения символа symbol в строку string. 
Возвращает указатель на первое вхождение символа в строке. 
Завершающий нулевой символ считается частью Си-строки. 
Таким образом, он также может быть найден для получения указателя на конец строки.
Указатель на первое вхождение символа в строку.
Если значение не найдено, функция возвращает нулевой указатель.
*/
char *my_strchr(const char *str, int symbol)
{
    const char *ptr_str = str;

    for (; *ptr_str; ptr_str++)
        if (*ptr_str == symbol)
            return (char *) ptr_str;

    if (*ptr_str == symbol)
        return (char *) ptr_str;
    return NULL;
}

/*
Функция strrchr() в C/C++ находит последнее вхождение символа в строку. 
Возвращает указатель на последнее вхождение в строке. 
Завершающий нулевой символ считается частью строки C. 
Поэтому она также может быть расположена для извлечения указателя на конец строки
*/
char *my_strrchr(const char *str, int symbol)
{
    const char *ptr_str = str;
    const char *elem = NULL;

    for (; *ptr_str; ptr_str++)
        if (*ptr_str == symbol)
            elem = ptr_str;

    if (*ptr_str == symbol)
        elem = ptr_str;
    return (char *) elem;
}

int main(void)
{
    int count_failed_tests = 0;

    if (my_strpbrk("Hello, world!", "I like milk") != strpbrk("Hello, world!", "I like milk"))
        count_failed_tests++;
    if (my_strpbrk("Hello, world!", "I") != strpbrk("Hello, world!", "I"))
        count_failed_tests++;

    if (my_strspn("geeeek", "geek") != strspn("geeeek", "geek"))
        count_failed_tests++;
    if (my_strspn("Hello, world!", "m") != strspn("Hello, world!", "m"))
        count_failed_tests++;
    if (my_strspn("Hello, world!", "le") != strspn("Hello, world!", "le"))
        count_failed_tests++;

    if (my_strcspn("Hello, world!", "milk") != strcspn("Hello, world!", "milk"))
        count_failed_tests++;
    if (my_strcspn("Hello, world!", "I") != strcspn("Hello, world!", "I"))
        count_failed_tests++;
    if (my_strcspn("Hello, world!", "le") != strcspn("Hello, world!", "le"))
        count_failed_tests++;

    if (my_strchr("Hello, world!", '\0') != strchr("Hello, world!", '\0'))
        count_failed_tests++;
    if (my_strchr("Hello, world!", 'o') != strchr("Hello, world!", 'o'))
        count_failed_tests++;
    if (my_strchr("Hello, world!", 'm') != strchr("Hello, world!", 'm'))
        count_failed_tests++;

    if (my_strrchr("Hello, world!", '\0') != strrchr("Hello, world!", '\0'))
        count_failed_tests++;
    if (my_strrchr("Hello, world!", 'o') != strrchr("Hello, world!", 'o'))
        count_failed_tests++;
    if (my_strrchr("Hello, world!", 'm') != strrchr("Hello, world!", 'm'))
        count_failed_tests++;
    printf("count_failed_tests: %d\n", count_failed_tests);
    return EXIT_SUCCESS;
}
