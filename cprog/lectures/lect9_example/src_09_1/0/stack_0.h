#ifndef _STACK_0_H_

#define _STACK_0_H_

#include <stdbool.h>

// TODO: не хватает значений кодов ошибок

void make_empty(void);

bool is_empty(void);

bool is_full(void);

int push(int i);

int pop(int *i);

#endif