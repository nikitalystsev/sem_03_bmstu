import ctypes

lib = ctypes.CDLL('example.dll')

# int add(int a, int b);
add = lib.add

add.argtypes = (ctypes.c_int, ctypes.c_int)
add.restype = ctypes.c_int

print(add(5, 3))

print(add(-8, 5))

x = 12
y = -7

print(add(x, y))