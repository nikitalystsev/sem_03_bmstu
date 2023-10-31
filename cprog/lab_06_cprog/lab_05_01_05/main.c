#include "max.h"
#include "process.h"

int main(void)  
{
    FILE *f = stdin;
    int count_equal;
    int rc;

    if ((rc = process(f, &count_equal)) != 0)
        return rc;

    printf("%d\n", count_equal);

    return EXIT_SUCCESS;
}
