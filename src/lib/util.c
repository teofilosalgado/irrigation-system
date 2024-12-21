#include "lib/delay.h"

int is_array_equal(const int * a, const int * b, unsigned int length) {
    unsigned int i = 0;
    for (i = 0; i < length; ++i) {
        if(a[i] != b[i]) { 
            return 0;
        }
    }
    return 1;
}

int sum_array(const int * a, unsigned int length) {
    int result = 0;
    unsigned int i = 0;
    for (i = 0; i < length; ++i) {
        result += a[i];
    }
    return result;
}