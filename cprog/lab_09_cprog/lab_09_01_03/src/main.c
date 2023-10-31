#include "defines.h"
#include "product.h"
#include "revise.h"

int main(int argc, char const *argv[])
{
    int rc = 0;

    double price;

    if ((rc = get_price(argc, argv, &price)) != 0)
    {
        return rc;
    }

    FILE *file;

    product_t *array_products;

    int count_products = 0;

    if ((file = fopen(argv[1], "r")) == NULL)
    {
        return ERR_OPEN_FILE;
    }

    if ((rc = get_count_products(&count_products, file)) != 0)
    {
        fclose(file);
        return rc;
    }

    if ((array_products = calloc(count_products, sizeof(product_t))) == NULL)
    {
        fclose(file);
        return ERR_ALLOC_MEM_ARRAY;
    }

    if ((rc = read_products(array_products, count_products, file)) != 0)
    {
        free_arr_products(array_products, count_products);
        fclose(file);
        return rc;
    }

    print_below_price_products(array_products, count_products, price);

    free_arr_products(array_products, count_products);

    fclose(file);

    return rc;
}
