#ifndef __MODELING_H__
#define __MODELING_H__

#include "defines.h"
#include "queue_array.h"
#include "queue_list.h"
#include "process.h"
#include "timing.h"

typedef struct param_t param_t;
typedef struct model_t model_t;

/// @brief Структура параметров моделирования
struct param_t
{
    double min_add_time;     // минимальное время добавления
    double max_add_time;     // максимальное время добавления
    double min_process_time; // минимальное время обработки
    double max_process_time; // максимальное время обработки
    int count_appl;          // количество обрабатываемых заявок
    int count_print_appl;    // диапазон заявок для вывода
};

/// @brief Структура, содержащая данные моделирования
struct model_t
{
    int curr_len_queue;      // текущая длина очереди
    double av_len_queue;     // средняя длина очереди
    double model_time;       // общее время моделирования
    double input_time;       // общее время добавления
    double output_time;      // общее время обработки
    double downtime;         // время простоя
    int count_input;         // количество вошедших заявок
    int count_output;        // количество вышедних заявок
    int count_calls_machine; // количество вызовов аппарата
    long double work_time;   // время работы (в микросекундах)
    int memory_size;         // затраченный обьем памяти (в байтах)
};

void fill_default_param(param_t *const param);

int model_arr(const param_t *const param);

int model_list(const param_t *const param, free_addr_t *const free_addrs);

#endif
