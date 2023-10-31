#ifndef __EXAMPLE__H__

#define __EXAMPLE__H__

#ifdef EXAMPLE_EXPORTS
#define EXAMPLE_DLL __declspec(dllexport)
#else
#define EXAMPLE_DLL __declspec(dllimport)
#endif

#define EXAMPLE_DECL __cdecl

EXAMPLE_DLL int EXAMPLE_DECL add(int a, int b);

EXAMPLE_DLL int EXAMPLE_DECL divide(int a, int b, int *remainder);

EXAMPLE_DLL void EXAMPLE_DECL fill_array(double *arr, int n);

EXAMPLE_DLL double EXAMPLE_DECL avg(double *arr, int n);

EXAMPLE_DLL int EXAMPLE_DECL filter(double *src, int src_len, double *dst, int *dst_len);

#endif // __EXAMPLE__H__
