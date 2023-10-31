/*
Слайды 8, 9
*/

#include <string.h>
#include <stdlib.h>

int main(void)
{
    struct book_t
    {
        char *title;
        int year;
        
    } a = { 0 }, b = { 0 };
    
    a.title = strdup("Book a");
    a.year = 2000;

    b.title = strdup("Book b");
    b.year = 2005;
    
    a = b;
    
    free(a.title);
    free(b.title);
    
    return 0;
}
