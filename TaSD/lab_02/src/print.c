#include "print.h"

void print_menu(void)
{
    printf("\nПрограмма для обработки данных о студентах.\n");
    printf("1 - Загрузить данные из файла\n"
           "2 - Вывести на экран общий список студентов\n"
           "3 - Вывести на экран отсортированную таблицу ключей\n"
           "4 - Вывети на экран список студентов указанного года поступления,\n"
           "    живущих в общежитии\n"
           "5 - Упорядочить и вывести данные по среднему баллу за сессию,\n"
           "    используя саму таблицу\n"
           "6 - Упорядочить и вывести данные по среднему баллу за сессию,\n"
           "    используя массив ключей\n"
           "7 - Добавить данные в таблицу\n"
           "8 - Удалить записи по среднему баллу за сессию\n"
           "9 - Вывести результаты сравнения эффективности программы\n"
           "    при обработке таблицы и массива ключей\n"
           "0 - Выйти из программы\n");
    printf("Выберите пункт меню:\n");
}

void print_student(student_t *const student)
{
    printf("|           surname            |             name              | group | gender | age | mark | year of adm |");
    if (student->flag)
    {
        printf("         street            | num home | num flat |\n");
    }
    else
    {
        printf("num dorm | num room |\n");
    }

    printf(" %-30s ", student->surname);
    printf(" %-30s ", student->name);
    printf("    %d    ", student->study_group);
    printf("    %d    ", student->gender);
    printf(" %2d  ", student->age);
    printf(" %3d  ", student->mark);
    printf("  %4d   ", student->year_adm);

    if (student->flag)
    {
        printf("        %-30s", student->house.home.street);
        printf("  %d     ", student->house.home.num_home);
        printf("  %d\n", student->house.home.num_flat);
    }
    else
    {
        printf("         %d", student->house.dorm.num_dorm);
        printf("         %d\n", student->house.dorm.num_room);
    }

    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void print_arr_students(
    student_t *const arr_students,
    const size_t count_students)
{
    if (count_students == 0)
    {
        printf("\nТаблица пустая.\n\n");
    }
    for (size_t i = 0; i < count_students; i++)
    {
        printf("\nЭлемент таблицы №%lu\n", i + 1);
        print_student(&arr_students[i]);
    }
}

void print_arr_students_by_keys(
    key_t *const arr_keys,
    student_t *const arr_students,
    const size_t count_students)
{
    if (count_students == 0)
    {
        printf("\nТаблица пустая.\n\n");
    }

    for (size_t i = 0; i < count_students; i++)
    {
        printf("\nЭлемент таблицы №%lu\n", i + 1);
        print_student(&arr_students[arr_keys[i].index_mark]);
    }
}

void print_key(
    const key_t *const key)
{
    printf("| index mark = %d | mark = %d |\n", key->index_mark, key->mark);
}

void print_keys(
    key_t *const arr_keys,
    const size_t count_students)
{
    for (size_t i = 0; i < count_students; i++)
    {
        print_key(&arr_keys[i]);
    }
}

void print_result_timing_students(long double time, bool check_qsort)
{
    if (check_qsort)
    {
        printf("Сортировка исходной таблицы с помощью быстрой сортировки qsort:\n");
        printf("%LF\n", time);
    }
    else
    {
        printf("\nСортировка исходной таблицы с помощью сортировки методом пузырька:\n");
        printf("%LF\n", time);
    }
}

void print_result_timing_keys(long double time, bool check_qsort)
{
    if (check_qsort)
    {
        printf("Сортировка массива ключей с помощью быстрой сортировки qsort:\n");
        printf("%LF\n", time);
    }
    else
    {
        printf("Сортировка массива ключей с помощью сортировки методом пузырька:\n");
        printf("%LF\n", time);
    }
}
