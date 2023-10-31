#ifndef __ARR__LIB__H__

#define __ARR__LIB__H__

// Макрос ARR_EXPORTS необходимо определить только при сборке DLL
#ifdef ARR_EXPORTS
#define ARR_DLL __declspec(dllexport)
#else
#define ARR_DLL __declspec(dllimport)
#endif

// Соглашение о вызовах
#define ARR_DECL __cdecl

ARR_DLL void ARR_DECL arr_form(int *arr, int n);

ARR_DLL void ARR_DECL arr_print(const int *arr, int n);

#endif  // __ARR__LIB__H__
