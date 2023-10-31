#include <stdio.h>

#define SUCCESS 0

int main(void)
{
    int count = 0;
    double sum = 0;
    double elem;

    if (scanf("%lf", &elem) == 1)
    {
        sum = sum + elem;
        count++;
    }

    while (scanf("%lf", &elem) == 1)
    {
        sum = sum + elem;
        count++;
    }

    printf("%lf", sum / count);

    return SUCCESS;
}