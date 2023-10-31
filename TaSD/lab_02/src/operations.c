#include "operations.h"

void delete_one_student(
    student_t *const arr_students,
    size_t *const count_students,
    size_t index_student)
{
    for (size_t i = index_student; i < *count_students - 1; i++)
    {
        arr_students[i] = arr_students[i + 1];
    }
}

void delete_one_key(
    key_t *const arr_keys,
    size_t *const count_students,
    size_t index_key)
{
    for (size_t i = index_key; i < *count_students - 1; i++)
    {
        arr_keys[i] = arr_keys[i + 1];
    }
}

void relac(
    key_t *const arr_keys,
    size_t *const count_students,
    size_t index_key)
{
    for (size_t i = index_key; i < *count_students - 1; i++)
    {
        arr_keys[i].index_mark = arr_keys[i + 1].index_mark;
    }
}

void delete_students_by_mark(
    student_t *const arr_students,
    size_t *const count_students,
    const int mark)
{
    size_t count = *count_students;

    for (size_t i = 0; i < *count_students; i++)
    {
        if (check_student_by_mark(&arr_students[i], mark))
        {
            delete_one_student(arr_students, count_students, i);
            (*count_students)--;
            i--;
        }
    }

    if (*count_students == count)
    {
        printf("\nСтудентов со средним баллом за сессию %d в таблице нет. Удалять нечего.\n\n", mark);
    }
    else
    {
        printf("\nСтуденты со средним баллом за сессию %d были успешно удалены из таблицы.\n\n", mark);
    }
}

int add_student(
    key_t *const arr_key,
    student_t *const arr_students,
    size_t *const count_students)
{
    if (*count_students + 1 > MAX_STUDENT)
    {
        printf("\nТаблица переполнена! Добавление данных невозможно.\n\n");
        return ERR_ADD_STUDENT;
    }

    int rc = 0;

    if ((rc = get_basic_info(&arr_students[*count_students])) != 0)
    {
        return rc;
    }

    if ((rc = get_variable_info(&arr_students[*count_students])) != 0)
    {
        return rc;
    }

    arr_key[*count_students].mark = arr_students[*count_students].mark;
    arr_key[*count_students].index_mark = *count_students + 1;

    (*count_students)++;

    printf("\nДанные о студенте были успешно добавлены в таблицу.\n\n");

    return rc;
}

void print_dorm_students_by_year(
    student_t *const arr_students,
    size_t count_students,
    const int year)
{
    int count = 0;
    for (size_t i = 0; i < count_students; i++)
    {
        if (check_dorm_student_by_year(&arr_students[i], year))
        {
            printf("\nЭлемент №%d\n", count + 1);
            print_student(&arr_students[i]);
            count++;
        }
    }

    if (count == 0)
    {
        printf("\nСтудентов, поступивших в %d году и живущих в общежитии, в таблице нет.\n\n", year);
    }
}

void get_arr_keys(
    key_t *const arr_keys,
    student_t *const arr_students,
    size_t count_students)
{
    for (size_t i = 0; i < count_students; i++)
    {
        arr_keys[i].index_mark = i;
        arr_keys[i].mark = arr_students[i].mark;
    }
}

void copy(
    key_t *const keys,
    key_t *const arr_keys,
    student_t *const students,
    student_t *const arr_students,
    const size_t count_students)
{
    for (size_t i = 0; i < count_students; i++)
    {
        memcpy(&keys[i], &arr_keys[i], sizeof(arr_keys[0]));
    }
    for (size_t i = 0; i < count_students; i++)
    {
        memcpy(&students[i], &arr_students[i], sizeof(arr_students[0]));
    }
}

void sort_comparison(
    key_t *const arr_keys,
    student_t *const arr_students,
    const size_t count_students)
{
    key_t keys[MAX_STUDENT];
    student_t students[MAX_STUDENT];

    long double beg, end;

    printf("\n%lu размер массива ключей (в байтах)", sizeof(keys[0]) * count_students);
    printf("\n%lu размер таблицы (в байтах)\n", sizeof(students[0]) * count_students);

    copy(keys, arr_keys, students, arr_students, count_students);

    beg = milliseconds_now();
    bubble_sort(students, count_students, sizeof(students[0]), compare_table);
    end = milliseconds_now();

    print_result_timing_students(end - beg, false);
    long double time1 = end - beg;
    copy(keys, arr_keys, students, arr_students, count_students);

    beg = milliseconds_now();
    qsort(students, count_students, sizeof(students[0]), compare_table);
    end = milliseconds_now();

    print_result_timing_students(end - beg, true);
    long double time2 = end - beg;

    beg = milliseconds_now();
    bubble_sort(keys, count_students, sizeof(keys[0]), compare_keys);
    end = milliseconds_now();

    print_result_timing_keys(end - beg, false);
    long double time3 = end - beg;
    copy(keys, arr_keys, students, arr_students, count_students);

    beg = milliseconds_now();
    qsort(keys, count_students, sizeof(keys[0]), compare_keys);
    end = milliseconds_now();

    print_result_timing_keys(end - beg, true);
    long double time4 = end - beg;
    printf("\nЭффективность сортировки пузырьком по отношению к быстрой сортировке в процентах (массив ключей)\n");
    printf("%Lf\n", ((100 * time4) / time3));
    printf("Эффективность сортировки пузырьком по отношению к быстрой сортировке в процентах (таблица)\n");
    printf("%Lf\n", ((100 * time2) / time1));
    printf("При сортировке исходной таблицы быстрая сортировка (qsort) эффективнее сортировки пузырьком на %.2LF процентов\n", 100 - ((100 * time2) / time1));
    printf("При сортировке таблицы ключей быстрая сортировка (qsort) эффективнее сортировки пузырьком на %.2LF процентов\n", 100 - ((100 * time4) / time3));
}

int execute_menu_item(
    key_t *const arr_keys,
    student_t *const arr_students,
    size_t *const count_students,
    int8_t menu_item)
{
    int year;
    int mark;
    int rc = 0;

    switch (menu_item)
    {
    case 1:
        if ((rc = get_data_from_file(arr_keys, arr_students, count_students)) != 0)
        {
            return rc;
        }
        printf("\nДанные были успешно загружены в таблицу.\n\n");
        break;
    case 2:
        print_arr_students(arr_students, *count_students);
        break;
    case 3:
        if (*count_students == 0)
        {
            printf("\nТаблица пустая\n\n");
            return 0;
        }
        bubble_sort(arr_keys, *count_students, sizeof(arr_keys[0]), compare_keys);
        print_keys(arr_keys, *count_students);
        break;
    case 4:
        if (*count_students == 0)
        {
            printf("\nТаблица пустая\n\n");
            return 0;
        }
        if ((rc = get_year_of_adm(&year)) != 0)
        {
            return rc;
        }
        print_dorm_students_by_year(arr_students, *count_students, year);
        break;
    case 5:
        if (*count_students == 0)
        {
            printf("\nТаблица пустая\n\n");
            return 0;
        }
        bubble_sort(arr_students, *count_students, sizeof(arr_students[0]), compare_table);
        printf("\nТаблица студентов была упорядочена по среднему баллу за сессию.\n\n");
        print_arr_students(arr_students, *count_students);
        break;
    case 6:
        if (*count_students == 0)
        {
            printf("\nТаблица пустая\n\n");
            return 0;
        }
        get_arr_keys(arr_keys, arr_students, *count_students);
        bubble_sort(arr_keys, *count_students, sizeof(arr_keys[0]), compare_keys);
        printf("\nТаблица ключей была упорядочена по среднему баллу за сессию.\n\n");
        print_arr_students_by_keys(arr_keys, arr_students, *count_students);
        break;
    case 7:
        if ((rc = add_student(arr_keys, arr_students, count_students)) != 0)
        {
            return rc;
        }
        break;
    case 8:
        if (*count_students == 0)
        {
            printf("\nТаблица пустая\n\n");
            return 0;
        }
        if ((rc = get_mark(&mark)) != 0)
        {
            return rc;
        }
        delete_students_by_mark(arr_students, count_students, mark);
        break;
    case 9:
        if (*count_students == 0)
        {
            printf("\nТаблица пустая\n\n");
            return 0;
        }
        sort_comparison(arr_keys, arr_students, *count_students);
        break;
    default:
        printf("Неправильный пункт меню. Пожалуйста, попробуйте еще раз.\n");
        return ERR_MENU_ITEM;
    }

    return rc;
}
