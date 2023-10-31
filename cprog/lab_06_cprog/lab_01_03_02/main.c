#include <stdio.h>
#define SUCCESS 0

double count_resistance(double r1, double r2, double r3)
{
    double r = (r1 * r2 * r3) / (r2 * r3 + r1 * r3 + r1 * r2);
    return r;
}

int main(void)
{
    double r1, r2, r3;
    double r;
    
    puts("Enter resistors resistance:");
    scanf("%lf %lf %lf", &r1, &r2, &r3);

    r = count_resistance(r1, r2, r3);

    printf("%lf\n", r);
    return SUCCESS;    
}
