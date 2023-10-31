import ctypes

lib = ctypes.CDLL('example.dll')

# int filter(double *src, int src_len, double *dst, int *dst_len);
_filter = lib.filter

_filter.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_int, ctypes.POINTER(ctypes.c_double), ctypes.POINTER(ctypes.c_int))
_filter.restype = ctypes.c_int

def filter(nums):
  n = len(nums)
  arr = (ctypes.c_double * n)(*nums)
  
  n_res = ctypes.c_int(0)
  
  rc = _filter(arr, n, None, n_res)
  if rc:
    res = (ctypes.c_double * n_res.value)()
	
    rc = _filter(arr, n, res, n_res)
	
    return rc, list(res)	
  else:
    return rc, list()
	
print(filter((-1, -2, -3, -4, -5)))

print(filter((1, 2, 3)))

print(filter((1, -2, 3, -4, 5)))

