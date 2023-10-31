#ifndef __READ_H__
#define __READ_H__

#include "defines.h"
#include "queue_array.h"
#include "queue_list.h"
#include "modeling.h"

int read_menu_item(int8_t *const item);

int read_size_queue_array(int *const size);

int read_queue_elem(int *const num);

int read_work_num(int *const number);

int read_task_menu_item(int8_t *const item);

int read_range_time(double *const min, double *const max);

#endif

