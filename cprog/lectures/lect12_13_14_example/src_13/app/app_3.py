import ctypes

lib = ctypes.CDLL('example.dll')

# void fill_array(double *arr, int n);
_fill_array = lib.fill_array

_fill_array.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_int)
_fill_array.restype = None

def fill_array(n):
  arr = (ctypes.c_double * n)()
  
  _fill_array(arr, n)
  
  return list(arr)
  
print(fill_array(5))
print(fill_array(3))