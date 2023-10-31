#include "revise.h"

int get_price(int argc, char const *argv[], double *const price)
{
    if (argc != 3)
    {
        return ERR_PARAM;
    }

    *price = atof(argv[2]);

    if (fabs(*price) < EPS)
    {
        return ERR_PRICE_PARAM;
    }

    if (*price < 0)
    {
        return ERR_PRICE_PARAM;
    }

    return EXIT_SUCCESS;
}
