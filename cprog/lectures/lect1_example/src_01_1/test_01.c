/*
Слайд 2
*/

#include <stdio.h>

int main(void)
{
    double d = 5.0;
    double *pd = &d;
    void *pv = pd;

    pd = pv;

    /*
    // error: dereferencing 'void *' pointer
    // error: invalid use of void expression
    printf("%d\n", *pv);
    */

    /*
    // error: dereferencing 'void *' pointer
    pv++;
    */

    return 0;
}