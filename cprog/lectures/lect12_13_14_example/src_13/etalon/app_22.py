import ctypes

lib = ctypes.CDLL('example.dll')

# int devide(int, int, int*)
_divide = lib.divide
_divide.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int))
_divide.restype = ctypes.c_int

def divide(x, y):
  rem = ctypes.c_int()
  quot = _divide(x, y, rem)
  return quot, rem.value

print(divide(7, 5))

print(divide(4, 2))
