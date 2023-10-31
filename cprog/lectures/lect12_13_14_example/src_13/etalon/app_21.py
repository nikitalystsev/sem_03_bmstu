import ctypes

lib = ctypes.CDLL('example.dll')

# int devide(int, int, int*)
_divide = lib.divide
_divide.argtypes = (ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_int))
_divide.restype = ctypes.c_int

x = 0

# Ups
_divide(7, 5, x)
