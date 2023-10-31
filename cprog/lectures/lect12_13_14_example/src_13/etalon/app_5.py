import ctypes

lib = ctypes.CDLL('example.dll')

# void filter(double*, int, double*, int)
_filter = lib.filter
_filter.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_int))
_filter.restype = ctypes.c_int

def filter(nums):
  src_len = len(nums)
  src = (ctypes.c_double * src_len)(*nums)
  dst_len = ctypes.c_int(0)

  rc = _filter(src, src_len, None, dst_len)

  if rc:
    dst = (ctypes.c_double * dst_len.value)()

    rc = _filter(src, src_len, dst, dst_len)

    return rc, list(dst)
  else:
    return rc, list()


print(filter((-1, -2, -3, -4, -5)))
print(filter((1, 2, 3, 4, 5)))
print(filter((1, -2, 3, -4, 5)))