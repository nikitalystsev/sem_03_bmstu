#ifndef __PRINT_H__
#define __PRINT_H__

#include "defines.h"
#include "modeling.h"

void print_task_menu(const param_t *const param);

void print_menu(void);

void print_intermediate(const model_t *const model);

void print_result(const model_t *const model, const param_t *const param);

int print_size_info(void);

int print_add_queue_time(void);

int print_pop_queue_time(void);

int print_clean_queue_time(void);

int print_create_queue_time(void);

int print_func_time(void);

#endif
