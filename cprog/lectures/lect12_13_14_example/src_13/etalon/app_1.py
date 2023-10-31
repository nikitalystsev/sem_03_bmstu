import ctypes

lib = ctypes.CDLL('example.dll')

# int add(int, int)
add = lib.add
add.argtypes = (ctypes.c_int, ctypes.c_int)
add.restype = ctypes.c_int

print(add(5, 6))

print(add(7, -2))