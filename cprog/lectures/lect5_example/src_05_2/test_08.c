/*
Слайд 12
*/

#include <string.h>
#include <stdlib.h>

struct book_t
{
    char *title;
    int year;
};

struct book_t* book_create(const char *title, int year)
{
    struct book_t *pbook = malloc(sizeof(struct book_t));
    
    if (pbook)
    {
        pbook->title = strdup(title);
        if (pbook->title)
        {
            pbook->year = year;
        }
        else
        {
            free(pbook);
            pbook = NULL;
        }
    }
    
    return pbook;
}

void book_free(struct book_t *pbook)
{
    if (!pbook)
        return;
	
    free(pbook->title);
    free(pbook);
}

void book_free_ex(struct book_t **pbook)
{
    if (!(*pbook))
        return;
	
    free((*pbook)->title);
    free(*pbook);
	
    *pbook = NULL;
}


int main(int argc, char **argv)
{
    struct book_t *pbook = NULL;
    
    pbook = book_create("Book a", 2000);
    if (pbook)
    {
        // Работа с книгой

        /*
        // Такое освобождение памяти приведет к утечке
        free(pbook);
        */
        // Правильно освобождать так 
        book_free(pbook);
        /*
        // или так
        book_free_ex(&pbook);
        */
    }
    
    return 0;
}

