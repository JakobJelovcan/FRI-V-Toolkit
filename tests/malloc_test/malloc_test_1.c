#include <stdlib.h>
#include <system/assert.h>

int main() {
    int* data_a = (int*) malloc(20 * sizeof(int));
    int* data_b = (int*) malloc(20 * sizeof(int));

    assert(data_a != data_b);

    for (int i = 0; i < 20; ++i) {
        data_a[i] = i;
        data_b[i] = (i + 10);
    }

    for (int i = 0; i < 20; ++i) {
        assert(data_a[i] == i && data_b[i] == i + 10);
    }

    free(data_a);
    free(data_b);
    return 0;
}