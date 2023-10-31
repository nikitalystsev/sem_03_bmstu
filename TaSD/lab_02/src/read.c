#include "read.h"

int get_basic_info(
    student_t *const student)
{
    int rc = 0;
    printf("\nВведите место, где проживает студент во время обучения (0 - общежитие, 1 - дом):\n");
    if (scanf("%d", &(student->flag)) != 1)
    {
        printf("Некорректный ввод места проживания!\n");
        return ERR_INPUT_HOUSE;
    }

    if (student->flag != 0 && student->flag != 1)
    {
        printf("Неверный ввод! Место проживания определяется цифрой: (0 - общежитие, 1 - дом).\n");
        return ERR_INPUT_HOUSE;
    }

    printf("\nВведите фамилию студента (не более 30 символов):\n");
    if (scanf("%s", student->surname) != 1)
    {
        printf("Некорректный ввод фамилии студента!\n");
        return ERR_INPUT_SURNAME;
    }

    if (strlen(student->surname) < 1 || strlen(student->surname) >= SURNAME_SIZE - 1)
    {
        printf("Неверный ввод! Фамилия студента не должна быть пустой строкой или быть более 30 символов.\n");
        return ERR_INPUT_SURNAME;
    }

    printf("\nВведите имя студента (не более 30 символов):\n");
    if (scanf("%s", student->name) != 1)
    {
        printf("Некорректный ввод имени студента!\n");
        return ERR_INPUT_NAME;
    }

    if (strlen(student->name) < 1 || strlen(student->surname) >= NAME_SIZE - 1)
    {
        printf("Неверный ввод! Имя студента не должна быть пустой строкой или быть более 30 символов.\n");
        return ERR_INPUT_NAME;
    }

    printf("\nВведите учебную группу студента (целое число от 1 до 6):\n");
    if (scanf("%d", &(student->study_group)) != 1)
    {
        printf("Некорректный ввод учебной группы!\n");
        return ERR_INPUT_STUDY_GROUP;
    }

    if (student->study_group < 1 || student->study_group > 6)
    {
        printf("Неверный ввод! Учебная группа - целое число от 1 до 6.\n");
        return ERR_INPUT_STUDY_GROUP;
    }

    printf("\nВведите пол обучающегося (0 - женский, 1 - мужской):\n");
    if (scanf("%d", &(student->gender)) != 1)
    {
        printf("Некорректный ввод пола обучающегося!\n");
        return ERR_INPUT_GENDER;
    }

    if (student->gender != 0 && student->gender != 1)
    {
        printf("Неверный ввод! Пол обучающегося определяется цифрой: (0 - женский, 1 - мужской).\n");
        return ERR_INPUT_GENDER;
    }

    printf("\nВведите возраст студента (целое число от 18 до 26):\n");
    if (scanf("%d", &(student->age)) != 1)
    {
        printf("Некорректный ввод возраста студента!\n");
        return ERR_INPUT_AGE;
    }

    if (student->age < 18 || student->age > 26)
    {
        printf("Неверный ввод! Возраст студента - целое число от 18 до 26.\n");
        return ERR_INPUT_AGE;
    }

    if ((rc = get_mark(&student->mark)) != 0)
    {
        return rc;
    }

    if ((rc = get_year_of_adm(&student->year_adm)) != 0)
    {
        return rc;
    }

    return EXIT_SUCCESS;
}

int get_variable_info(
    student_t *const student)
{
    if (student->flag)
    {
        printf("\nВведите улицу, на которой проживает студент (не более 30 символов):\n");
        if (scanf("%s", student->house.home.street) != 1)
        {
            printf("Некорректный ввод улицы, на которой проживает студент!\n");
            return ERR_INPUT_STREET;
        }

        if (strlen(student->house.home.street) < 1 || strlen(student->house.home.street) >= STREET_SIZE - 1)
        {
            printf("Неверный ввод! Улица, на которой проживает студент не может быть пустой строкой или быть больше 30 символов.\n");
            return ERR_INPUT_STREET;
        }

        printf("\nВведите номер дома, в котором проживает студент (целое > 0):\n");
        if (scanf("%d", &(student->house.home.num_home)) != 1)
        {
            printf("Некорректный ввод номера дома, в котором проживает студент!\n");
            return ERR_INPUT_NUM_HOME;
        }
        if (student->house.home.num_home <= 0)
        {
            printf("Неверный ввод! Номер дома - целое число > 0\n");
            return ERR_INPUT_NUM_HOME;
        }

        printf("\nВведите номер квартиры, в которой проживает студент (целое > 0):\n");
        if (scanf("%d", &(student->house.home.num_flat)) != 1)
        {
            printf("Некорректный ввод номера квартиры, в которой проживает студент!\n");
            return ERR_INPUT_NUM_FLAT;
        }
        if (student->house.home.num_flat <= 0)
        {
            printf("Неверный ввод! Номер квартиры - целое число > 0\n");
            return ERR_INPUT_NUM_FLAT;
        }
    }
    else
    {
        printf("\nВведите общежития, в котором проживает студент:\n");
        if (scanf("%d", &(student->house.dorm.num_dorm)) != 1)
        {
            printf("Некорректный ввод номера общежития, в котором проживает студент!\n");
            return ERR_INPUT_NUM_DORM;
        }
        if (student->house.dorm.num_dorm <= 0)
        {
            printf("Неверный ввод! Номер общежития - целое число > 0\n");
            return ERR_INPUT_NUM_DORM;
        }
        

        printf("\nВведите номер комнаты, в которой проживает студент:\n");
        if (scanf("%d", &(student->house.dorm.num_room)) != 1)
        {
            printf("Некорректный ввод номера комнаты, в которой проживает студент!\n");
            return ERR_INPUT_ROOM;
        }
        if (student->house.dorm.num_room <= 0)
        {
            printf("Неверный ввод! Номер комнаты - целое число > 0\n");
            return ERR_INPUT_ROOM;
        }
        
    }

    return EXIT_SUCCESS;
}

int get_mark(int *mark)
{
    printf("\nВведите средний балл за сессию (целое число от 60 до 100):\n");

    if (scanf("%d", mark) != 1)
    {
        printf("Некорректный ввод среднего балла за сессию!\n");
        return ERR_INPUT_MARK;
    }

    if (*mark < MIN_MARK || *mark > MAX_MARK)
    {
        printf("Неверный ввод! Средний балл за сессию - целое число от 60 до 100.\n");
        return ERR_INPUT_MARK;
    }

    return EXIT_SUCCESS;
}

int get_year_of_adm(int *year)
{
    printf("\nВведите желаемый год поступления (целое число от 2015 до 2022):\n");

    if (scanf("%d", year) != 1)
    {
        printf("Некорректный ввод года поступления!\n");
        return ERR_YEAR_OF_ADM;
    }

    if (*year < MIN_YEAR || *year > MAX_YEAR)
    {
        printf("Неверный ввод! Год поступления - целое число от 2015 до 2022\n");
        return ERR_YEAR_OF_ADM;
    }

    return EXIT_SUCCESS;
}

int get_file_size(FILE *data_file, size_t *const file_size)
{
    if (fscanf(data_file, "%lu", file_size) != 1)
    {
        return ERR_SIZE_DATA_FILE;
    }

    if (*file_size > MAX_STUDENT || *file_size < 1)
    {
        return ERR_SIZE_DATA_FILE;
    }

    return EXIT_SUCCESS;
}

int get_data_from_file(
    key_t *const arr_keys,
    student_t *const arr_students,
    size_t *const count_student)
{
    int rc = 0;
    FILE *file;
    size_t file_size;

    if ((file = fopen(DATA_FILE, "r")) == NULL)
    {
        printf("Ошибка чтения данных из файла.\n");
        return ERR_OPEN_FILE;
    }

    if ((rc = get_file_size(file, &file_size)) != 0)
    {
        fclose(file);
        return rc;
    }

    for (size_t i = 0; i < file_size; i++, rc = 0)
    {
        rc += fscanf(file, "%d", &arr_students[i].flag);
        rc += fscanf(file, "%s", arr_students[i].surname);
        if (strlen(arr_students[i].surname) < 1 || strlen(arr_students[i].surname) >= SURNAME_SIZE - 1)
        {
            fclose(file);
            printf("Ошибка чтения данных из файла.\n");
            return ERR_GET_DATA_FROM_FILE;
        }
        rc += fscanf(file, "%s", arr_students[i].name);
        if (strlen(arr_students[i].name) < 1 || strlen(arr_students[i].name) >= NAME_SIZE - 1)
        {
            fclose(file);
            printf("Ошибка чтения данных из файла.\n");
            return ERR_GET_DATA_FROM_FILE;
        }
        rc += fscanf(file, "%d", &arr_students[i].study_group);
        rc += fscanf(file, "%d", &arr_students[i].gender);
        rc += fscanf(file, "%d", &arr_students[i].age);
        rc += fscanf(file, "%d", &arr_students[i].mark);
        arr_keys[i].mark = arr_students[i].mark;
        arr_keys[i].index_mark = i;
        rc += fscanf(file, "%d", &arr_students[i].year_adm);

        if (rc != 8)
        {
            fclose(file);
            printf("Ошибка чтения данных из файла.\n");
            return ERR_GET_DATA_FROM_FILE;
        }

        if (arr_students[i].flag == 1)
        {
            rc += fscanf(file, "%s", arr_students[i].house.home.street);
            if (strlen(arr_students[i].house.home.street) < 1 || strlen(arr_students[i].house.home.street) >= STREET_SIZE - 1)
            {
                fclose(file);
                printf("Ошибка чтения данных из файла.\n");
                return ERR_GET_DATA_FROM_FILE;
            }
            rc += fscanf(file, "%d", &arr_students[i].house.home.num_home);
            rc += fscanf(file, "%d", &arr_students[i].house.home.num_flat);

            if (rc != 11)
            {
                fclose(file);
                printf("Ошибка чтения данных из файла.\n");
                return ERR_GET_DATA_FROM_FILE;
            }
        }
        else
        {
            rc += fscanf(file, "%d", &arr_students[i].house.dorm.num_dorm);
            rc += fscanf(file, "%d", &arr_students[i].house.dorm.num_room);

            if (rc != 10)
            {
                fclose(file);
                printf("Ошибка чтения данных из файла.\n");
                return ERR_GET_DATA_FROM_FILE;
            }
        }
    }

    fclose(file);
    *count_student = file_size;

    return rc;
}
