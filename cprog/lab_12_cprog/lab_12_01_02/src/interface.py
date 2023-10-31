import ctypes

lib = ctypes.CDLL("../lib/libarr.dll")

_shift_left = lib.cyclic_shift_left_by_k
_shift_left.argtypes = (ctypes.POINTER(ctypes.c_int),
                        ctypes.c_int, ctypes.c_int)
_shift_left.restype = None

_get_count_square = lib.get_count_square
_get_count_square.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_get_count_square.restype = ctypes.c_int


_copy_by_square = lib.copy_arr_by_square
_copy_by_square.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int,
                            ctypes.POINTER(ctypes.c_int), ctypes.c_int)
_copy_by_square.restype = None


def shift_left(array, size, k):

    array = (ctypes.c_int * size)(*array)

    _shift_left(array, size, k)

    return list(array)


def copy_by_square(array, size):

    array = (ctypes.c_int * size)(*array)

    new_size = get_count_square(array, size)

    # new_size = size

    new_array = (ctypes.c_int * new_size)()

    _copy_by_square(array, size, new_array, new_size)

    return list(new_array)


def get_count_square(array, size):

    array = (ctypes.c_int * size)(*array)

    return _get_count_square(array, size)


def input_array():

    try:
        size = int(input("Введите целое число - размер массива: "))
    except (TypeError, ValueError):
        print("Невалидный ввод размерности массива!")
        return -1

    array = []

    for i in range(0, size):
        try:
            elem = int(input("Введите целое число - элемент массива: "))
        except (TypeError, ValueError):
            print("Невалидный ввод элемента массива!")
            return -1
        array.append(elem)

    return array


def main():

    array = input_array()

    if (array == -1):
        return

    print("Введенный массив:", array, sep="\n")

    new_arr_square = copy_by_square(array, len(array))
    
    print("Массив только из полных квадратов:", new_arr_square, sep="\n")

    try:
        k = int(input("Введите целое число - число для сдвига: "))
    except (TypeError, ValueError):
        print("Невалидный ввод размерности массива!")
        return 

    new_arr_shift_left = shift_left(array, len(array), k)

    print("Массив, циклически сдвинутый влево на %d:" % k, new_arr_shift_left, sep="\n")


if __name__ == "__main__":
    main()

