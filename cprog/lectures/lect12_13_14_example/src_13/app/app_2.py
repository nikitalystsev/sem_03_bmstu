import ctypes

lib = ctypes.CDLL('example.dll')

# int divide(int a, int b, int *remainder);
_divide = lib.divide

_divide.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int))
_divide.restype = ctypes.c_int

def divide(a, b):
  x = ctypes.c_int()
  
  y = _divide(a, b, x)
  
  return y, x.value


print(divide(5, 2))
print(divide(6, 2))
