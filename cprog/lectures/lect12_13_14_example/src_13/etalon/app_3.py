import ctypes

lib = ctypes.CDLL('example.dll')

# void avg(double*, int)
_avg = lib.avg
_avg.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_int)
_avg.restype = ctypes.c_double

def avg(nums):
  src_len = len(nums)
  src = (ctypes.c_double * src_len)(*nums)

  return _avg(src, src_len)


print(avg([1, 2, 3, 4, 5]))

print(avg([1]))