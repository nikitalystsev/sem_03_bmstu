#include "Python.h"
#include "example.h"


// int add(int a, int b);
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


// ������ ��⮤�� �����
static PyMethodDef example_methods[] =
{
    {"add", py_add, METH_VARARGS, "Integer addition"},
    {"divide", py_divide, METH_VARARGS, "Integer division"},
    { NULL, NULL, 0, NULL}
};


// �������, ����뢠��� �����
static struct PyModuleDef example_dll_module =
{
    PyModuleDef_HEAD_INIT,
    "example_dll",		// ��� �����
    "An example_dll module",	// ��ப� ��� ���㬥��樨
    -1,
    example_methods		// ������ ��⮤��
};


// �㭪�� ���樠����樨 �����
PyMODINIT_FUNC PyInit_example_dll(void)
{
    return PyModule_Create(&example_dll_module);
}
