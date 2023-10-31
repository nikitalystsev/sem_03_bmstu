#define _POSIX_C_SOURCE 200809L

#include "product.h"

int get_count_products(int *count_products, FILE *file)
{
    if (fscanf(file, "%d\n", count_products) != 1)
    {
        return ERR_READ_COUNT_PRODUCT;
    }

    if (*count_products <= 0)
    {
        return ERR_COUNT_PRODUCT;
    }

    return EXIT_SUCCESS;
}

int read_title_product(product_t *const product, FILE *file)
{
    size_t n = 0;
    product->title = NULL;
    int rc = 0;

    if ((rc = getline(&product->title, &n, file)) == -1)
    {
        return rc;
    }

    product->title[strlen(product->title) - 1] = '\0';

    return EXIT_SUCCESS;
}

int read_product(product_t *const product, FILE *file)
{
    if (read_title_product(product, file) != 0)
    {
        return ERR_READ_TITLE;
    }

    if (fscanf(file, "%d\n", &product->price) != 1)
    {
        return ERR_READ_PRICE;
    }

    if (product->price <= 0)
    {
        return ERR_PRICE;
    }

    return EXIT_SUCCESS;
}

int read_products(product_t *const array_products,
int count_products,
FILE *file)
{
    int rc = 0;

    for (int i = 0; i < count_products; i++)
    {
        if ((rc = read_product(&array_products[i], file)) != 0)
        {
            return rc;
        }
    }

    return rc;
}

void free_arr_products(product_t *const array_products,
int count_products)
{
    for (int i = 0; i < count_products; i++)
    {
        free(array_products[i].title);
    }

    free(array_products);
}

void print_below_price_products(product_t *const array_products,
int count_products,
double price)
{
    for (int i = 0; i < count_products; i++)
    {
        if (array_products[i].price < price)
        {
            printf("%s\n", array_products[i].title);
            printf("%d\n", array_products[i].price);
        }
    }
}
