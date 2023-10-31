#include <stdio.h>
#include <math.h>
#define SUCCESS 0

double count_len(double x2, double y2, double x1, double y1)
{
    double len = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return len;
}

double count_perimeter(double x1, double y1, double x2, double y2, double x3,
double y3)
{
    double len1 = count_len(x2, y2, x1, y1);
    double len2 = count_len(x3, y3, x2, y2);
    double len3 = count_len(x3, y3, x1, y1);
    double perimeter = len1 + len2 + len3;
    return perimeter;
}

int main(void)
{
    double x1, y1, x2, y2, x3, y3;
    double p;
	
    puts("Enter the coordinates points:");
    scanf("%lf %lf %lf %lf %lf %lf", &x1, &y1, &x2, &y2, &x3, &y3);

    p = count_perimeter(x1, y1, x2, y2, x3, y3);
	
    printf("%lf\n", p);
    return SUCCESS;
}
