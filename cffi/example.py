from _ext import lib, ffi
import numpy as np


def example():
    array = np.zeros([10], dtype=np.float64)
    array_ptr = ffi.cast('double*', array.ctypes.data)
    lib.set_array(array_ptr, 10)

    array_2d = np.zeros([10, 2], dtype=np.float64)
    array_2d = np.ascontiguousarray(array_2d)
    array_2d_ptr = ffi.cast('double*', array_2d.ctypes.data)
    lib.set_array_2d(array_2d_ptr, 10, 2)


if __name__ == '__main__':
    example()

