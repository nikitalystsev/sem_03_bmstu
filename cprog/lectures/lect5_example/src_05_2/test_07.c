/*
Слайд 11
*/

#include <string.h>
#include <stdlib.h>

struct book_t
{
	char *title;
	int year;
	
};

int book_copy(struct book_t *dst, const struct book_t *src)
{
    char *ptmp = strdup(src->title);

    if (ptmp)
    {
        free(dst->title);
    
        dst->title = ptmp;
        dst->year  = src->year;

        return 0;
    }

    return 1;
}

/*
// "Плохой" вариант функции
int book_copy(struct book_t *dst, const struct book_t *src)
{
    free(dst->title);
    
    dst->title = strdup(src->title);
    if (!dst->title)
        return 1;
    
    dst->year = src->year;
    
    return 0;
}
*/

int main(void)
{
    struct book_t a = { 0 }, b = { 0 };
    
    a.title = strdup("Book a");
    a.year = 2000;

    b.title = strdup("Book b");
    b.year = 2005;
    
    book_copy(&b, &a);
	
    free(a.title);
    free(b.title);
    
    return 0;
}
