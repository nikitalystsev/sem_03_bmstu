#ifndef _EXAMPLE_H_

#define _EXAMPLE_H_

int add(int a, int b);

int divide(int a, int b, int *remainder);

void fill_array(double *arr, int n);

int filter(double *src, int src_len, double *dst, int *dst_len);

double avg(double *arr, int n);

#endif