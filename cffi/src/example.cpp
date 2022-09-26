#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

int plus(int a, int b) {
    return a + b;
}

int minus(int a, int b) {
    return a - b;
}

void set_array(double* array, int n) {
    for (int i = 0; i < n; i++)
        array[i] = i;
}


void set_array_2d(double* array, int row, int col) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++)
            array[i * col + j] = i * col + j;
    }
}


#ifdef __cplusplus
}
#endif




