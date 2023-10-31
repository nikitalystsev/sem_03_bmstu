import ctypes

lib = ctypes.CDLL('example.dll')

# double avg(double *arr, int n);
_avg = lib.avg

_avg.argtypes = (ctypes.POINTER(ctypes.c_double), ctypes.c_int)
_avg.restype = ctypes.c_double

def avg(nums):
  n = len(nums)
  arr = (ctypes.c_double * n)(*nums)
  
  return _avg(arr, n)
  

# 2.5
print(avg((1, 2, 3, 4))) 

# 3
print(avg([2, 4])) 
