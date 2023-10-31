#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct dyn_array
{
    int len;
    int allocated;
    int step;
    int *data;
};


#define INIT_SIZE 1


void init_dyn_array(struct dyn_array *d)
{
    d->len = 0;
    d->allocated = 0;
    d->step = 2;
    d->data = NULL;
}


int append(struct dyn_array *d, int item)
{
    if (!d->data)
    {
        d->data = malloc(INIT_SIZE * sizeof(int));

        if (!d->data)
            return -1;

        d->allocated = INIT_SIZE;
    }
    else
        if (d->len >= d->allocated)
        {
            int *tmp = realloc(d->data, 
                        d->allocated * d->step * sizeof(int));

            if (!tmp)
                return -1;

            d->data = tmp;
            d->allocated *= d->step;
        }

    d->data[d->len] = item;
    d->len++;

    return 0;
}


int delete(struct dyn_array *d, int index)
{
    if (index < 0 || index >= d->len)
        return -1;

    memmove(d->data + index, d->data + index + 1,
                      (d->len - index - 1) * sizeof(int));
    d->len--;

    return 0;
}


void print(const struct dyn_array *d)
{
    printf("Array:\n");

    for (int i = 0; i < d->len; i++)
        printf("%d ", d->data[i]);

    printf("\n");
}


int main(void)
{
    struct dyn_array d;
    int rc;

    init_dyn_array(&d);

    rc = append(&d, 1);
    assert(rc == 0);

    rc = append(&d, 2);
    assert(rc == 0);

    rc = append(&d, 3);
    assert(rc == 0);

    rc = append(&d, 4);
    assert(rc == 0);

    rc = append(&d, 5);
    assert(rc == 0);

    print(&d);

    rc = delete(&d, 2);
    assert(rc == 0);

    print(&d);

    free(d.data);

    return 0;
}