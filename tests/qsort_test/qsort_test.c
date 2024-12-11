#include <inttypes.h>
#include <stdbool.h>
#include <stddef.h>
#include <system/assert.h>

int32_t values[100] = {40, 17, 18, 26, 51, 13, 34, 46, 45, 83, 26, 90, 26, 100, 51, 65, 70, 11, 5,  65, 55, 93, 79, 40, 91,
                       77, 48, 91, 96, 6,  19, 85, 42, 95, 35, 21, 32, 19, 12,  99, 62, 58, 44, 12, 3,  92, 15, 46, 9,  53,
                       58, 42, 57, 84, 92, 52, 33, 70, 17, 25, 59, 0,  13, 2,   37, 52, 28, 28, 47, 21, 38, 93, 6,  53, 49,
                       45, 78, 55, 6,  99, 60, 70, 63, 76, 68, 84, 50, 91, 91,  45, 51, 45, 39, 43, 18, 18, 18, 29, 56, 10};

__attribute__((always_inline)) static inline void swap(int32_t a[], int32_t x1, int32_t x2) {
    int32_t t = a[x1];
    a[x1] = a[x2];
    a[x2] = t;
}

int32_t partition(int32_t a[], int32_t left, int32_t right) {
    int32_t pivot = a[left];

    int32_t l = left;
    int32_t r = right + 1;

    while (true) {
        do
            ++l;
        while (a[l] < pivot && l < right);

        do
            --r;
        while (a[r] > pivot);

        if (l >= r)
            break;

        swap(a, l, r);
    }
    swap(a, left, r);
    return r;
}

static void _qsort(int32_t a[], int32_t left, int32_t right) {
    if (left < right) {
        int32_t r = partition(a, left, right);
        _qsort(a, left, r - 1);
        _qsort(a, r + 1, right);
    }
}

void qsort(int32_t a[], int32_t size) {
    _qsort(a, 0, size - 1);
}

int main() {
    qsort(values, 100);

    int32_t sum = values[0];
    for (uint32_t i = 1; i < 100; ++i) {
        assert(values[i - 1] <= values[i]);
        sum += values[i];
    }

    assert(values[0] == 0);
    assert(values[23] == 21);
    assert(values[40] == 40);
    assert(values[67] == 58);
    assert(values[99] == 100);
    assert(sum == 4775);
    
    return 0;
}