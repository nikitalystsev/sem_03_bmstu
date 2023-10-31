#include <stdlib.h>
#include "Python.h"
#include "example.h"


// int int add(int a, int b);
static PyObject* py_add(PyObject *self, PyObject *args)
{
    int a, b, c;

    if (!PyArg_ParseTuple(args,"ii", &a, &b))
        return NULL;

    c = add(a, b);
	
    return Py_BuildValue("i", c);
}


// int divide(int, int, int *);
static PyObject* py_divide(PyObject *self, PyObject *args)
{
    int a, b, quotient, remainder;

    if (!PyArg_ParseTuple(args, "ii", &a, &b))
        return NULL;

    quotient = divide(a,b, &remainder);

    return Py_BuildValue("(ii)", quotient, remainder);
}
                                 

static PyObject* copy_to_py_list(const double *arr, int n)
{
    PyObject *plist, *pitem;

    plist = PyList_New(n);
    if (!plist)
        return NULL;

    for (int i = 0; i < n; i++)
    {
        pitem = PyFloat_FromDouble(arr[i]);
        if (!pitem)
        {
            Py_DECREF(plist);
            return NULL;
        }

        PyList_SET_ITEM(plist, i, pitem);
    }

    return plist;
}


// void fill_array(double *arr, int n);
static PyObject* py_fill_array(PyObject *self, PyObject *args)
{
    PyObject *plist;
    int n;
    double *pbuf;

    if (!PyArg_ParseTuple(args, "i", &n))
        return NULL;

    pbuf = malloc(n * sizeof(double));
    if (!pbuf)
        return NULL;

    fill_array(pbuf, n);

    plist = copy_to_py_list(pbuf, n);

    free(pbuf);

    return plist;
}


static PyObject *py_avg(PyObject *self, PyObject *args)
{
    PyObject *seq, *item, *item_float;
    double *a;
    int n;
    double res;

    // Получим аргументы как последовательность объетов Python
    if (!PyArg_ParseTuple(args, "O", &seq))
        return NULL;

    seq = PySequence_Fast(seq, "Argument must be iterable");
    if (!seq)
        return NULL;

    //
    // Преобразуем последовательность в массив double (если получится)
    //

    n = PySequence_Fast_GET_SIZE(seq);

    a = malloc(n * sizeof(double));
    if (!a)
    {
        Py_DECREF(seq);

        return NULL;
    }

    for (int i = 0; i < n; i++)
    {
        item = PySequence_Fast_GET_ITEM(seq, i);
        if (!item)
        {
            Py_DECREF(seq);
            free(a);

            return NULL;
        }

        item_float = PyNumber_Float(item);
        if (!item_float)
        {
            Py_DECREF(seq);
            free(a);

            return NULL;
        }

        a[i] = PyFloat_AS_DOUBLE(item_float);

        Py_DECREF(item_float);
    }    

    // Освободим последовательность
    Py_DECREF(seq);

    res = avg(a, n);

    free(a);

    return Py_BuildValue("d", res);
}


static PyObject *py_avg_2(PyObject *self, PyObject *args)
{
    PyObject *obj, *iterator, *item;
    double *a;
    int n, i, bad_data;
    double res;

    // Получим аргументы как последовательность объетов Python
    if (!PyArg_ParseTuple(args, "O", &obj))
    {
        PyErr_SetString(PyExc_TypeError, "Cant parse arguments");

        return NULL;
    }

    iterator = PyObject_GetIter(obj);
    if (!iterator)
    {
        PyErr_SetString(PyExc_TypeError, "Cant get iterator");

        return NULL;
    }

    // Посчитаем количество
    n = 0;
    bad_data = 0;
    while ((item = PyIter_Next(iterator)) && !bad_data)
    {
        if (!PyFloat_Check(item) && !PyLong_Check(item))
        {
            bad_data = 1;
        }
        else
        {
            n++;
        }

        Py_DECREF(item);
    }

    Py_DECREF(iterator);

    if (bad_data)
    {
        Py_DECREF(obj);

        PyErr_SetString(PyExc_TypeError, "Bad arguments (only numbers are required)");

        return NULL;
    }

    a = malloc(n * sizeof(double));
    if (!a)
    {
        Py_DECREF(obj);

        PyErr_SetString(PyExc_TypeError, "Memory allocation error");

        return NULL;
    }

    iterator = PyObject_GetIter(obj);

    i = 0;
    while ((item = PyIter_Next(iterator)))
    {
        a[i] = PyFloat_AsDouble(item);
        i++;
        Py_DECREF(item);
    }

    Py_DECREF(iterator);

    Py_DECREF(obj);

    res = avg(a, n);

    free(a);

    return Py_BuildValue("d", res);
}


// Таблица методов модуля
static PyMethodDef example_methods[] =
{
    {"add", py_add, METH_VARARGS, "Integer addition"},
    {"divide", py_divide, METH_VARARGS, "Integer division"},
    {"fill_array", py_fill_array, METH_VARARGS, "Filling array of doubles"},
    {"avg", py_avg, METH_VARARGS, "Calculation of avarage value of array of doubles"},
    {"avg_2", py_avg_2, METH_VARARGS, "Calculation of avarage value of array of doubles"},
    { NULL, NULL, 0, NULL}
};


// Структура, описывающая модуль
static struct PyModuleDef example_dll_module =
{
    PyModuleDef_HEAD_INIT,
    "example_dll",		// Имя модуля
    "An example_dll module",	// Строка для документации
    -1,
    example_methods		// Таблица методов
};


// Функция инициализации модуля
PyMODINIT_FUNC PyInit_example_dll(void)
{
    return PyModule_Create(&example_dll_module);
}
