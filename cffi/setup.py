import os


os.system('gcc -shared src/example.cpp -c -o src/example.cpp.o -fopenmp -fPIC -O2 -std=c++11')


from cffi import FFI
ffibuilder = FFI()


# cdef() expects a string listing the C types, functions and
# globals needed from Python. The string follows the C syntax.
with open(os.path.join(os.path.dirname(__file__), "src/ext.h")) as f:
    ffibuilder.cdef(f.read())


ffibuilder.set_source(
    "_ext",
    """
    #include "src/ext.h"   // the C header of the library
    """,
    extra_objects=['src/example.cpp.o'],
    libraries=['stdc++']
)


if __name__ == "__main__":
    ffibuilder.compile(verbose=True)
    os.system("rm src/*.o")
    os.system("rm *.o")

