// ВНИМАНИЕ
// Пример содержит ОШИБКУ

#include <stdio.h>
#include <stdlib.h>

struct date
{
    int day;
    int month;
    int year;
};

struct date* create_date(int day, int month, int year)
{
    struct date *p = NULL;

    p = malloc(sizeof(p));
    if (p)
    {
        p->day = day;
        p->month = month;
        p->year = year;
    }
    
    return p;
}

int main(void)
{
    struct date *today = NULL;
    
    today = create_date(1, 9, 2020);
    if (today)
    {
        printf("%02d.%02d.%04d", today->day, today->month, today->year);
        
        free(today);
    }
    
    return 0;
}
