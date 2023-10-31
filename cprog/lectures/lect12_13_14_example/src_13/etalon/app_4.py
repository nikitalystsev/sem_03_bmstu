import ctypes

lib = ctypes.CDLL('example.dll')

# void fill_array(double*, int)
_fill_array = lib.fill_array
_fill_array.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_int)
_fill_array.restype = None


def fill_array(num):
  arr = (ctypes.c_double*num)()

  _fill_array(arr, num)

  return list(arr)


print(fill_array(5))

print(fill_array(10))