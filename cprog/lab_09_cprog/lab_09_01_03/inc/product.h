#ifndef __PRODUCT_H__
#define __PRODUCT_H__

#include "defines.h"

typedef struct 
{
    char *title;
    int price;
} product_t;

int get_count_products(int *count_products, FILE *file);

int read_title_product(product_t *const product, FILE *file);

int read_product(product_t *const product, FILE *file);

int read_products(product_t *const array_products,
int count_products, 
FILE *file);

void free_arr_products(product_t *const array_products,
int count_products);

void print_below_price_products(product_t *const array_products,
int count_products,
double price);

#endif
