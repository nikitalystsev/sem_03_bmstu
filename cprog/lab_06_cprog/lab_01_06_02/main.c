#include <stdio.h>
#include <math.h>
#define EPS 1e-9
#define ERROR 1
#define ALL_POINTS_MATCH 2
#define POINTS_ON_LINE 3
#define SUCCESS 0
#define CORRECT_INPUT 8

int check_coordinates(double xa, double ya, double xb, double yb, double xc,
double yc)
{ 
    if ((fabs(xa - xb) < EPS) && 
        (fabs(xb - xc) < EPS) && 
        (fabs(ya - yb) < EPS) && 
        (fabs(yb - yc) < EPS))
    {
        printf("Error: all points match");
        return ALL_POINTS_MATCH;
    }	
    else if (fabs(((xb - xa) * (yc - ya)) -
        ((yb - ya) * (xc - xa))) < EPS)
    {
        printf("Error: points lie on the same line");
        return POINTS_ON_LINE;
    }
    return SUCCESS;
}

double count_vector_prod(double xa, double ya, double xb, double yb, double xp,
double yp)
{
    double vector_prod = (xa - xp) * (yb - ya) - (xb - xa) * (ya - yp);
    return vector_prod;
}

void where_is_the_dot(double xa, double ya, double xb, double yb, double xc,
double yc,
double xp,
double yp)
{ 
    double vprod1 = count_vector_prod(xa, ya, xb, yb, xp, yp);
    double vprod2 = count_vector_prod(xb, yb, xc, yc, xp, yp);
    double vprod3 = count_vector_prod(xc, yc, xa, ya, xp, yp);

    if (((vprod1 > 0) && (vprod2 > 0) && (vprod3 > 0)) ||
        ((vprod1 < 0) && (vprod2 < 0) && (vprod3 < 0)))
        printf("0");
    else if ((fabs(vprod1) < EPS) ||
        (fabs(vprod2) < EPS) ||
        (fabs(vprod3) < EPS))
        printf("1");
    else
        printf("2");
}

int main(void)
{
    double xa, ya, xb, yb, xc, yc;
    double xp, yp;
    int rc;

    puts("Enter coordinates points:");
    rc = scanf("%lf %lf", &xa, &ya);
    rc += scanf("%lf %lf", &xb, &yb);
    rc += scanf("%lf %lf", &xc, &yc);
    rc += scanf("%lf %lf", &xp, &yp);

    if (rc != CORRECT_INPUT)
    {	    
        printf("Error: wrong input");
        return ERROR;
    }	
    	    
    rc = check_coordinates(xa, ya, xb, yb, xc, yc);
    if (rc == ALL_POINTS_MATCH)
        return ALL_POINTS_MATCH;
    else if (rc == POINTS_ON_LINE)
        return POINTS_ON_LINE;
 
    
    where_is_the_dot(xa, ya, xb, yb, xc, yc, xp, yp);
    return SUCCESS;
}
