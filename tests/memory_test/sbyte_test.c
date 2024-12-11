#include <inttypes.h>
#include <system/assert.h>
#include <stdlib.h>

#define NELEMENTS 512
#define STEP 64

volatile int8_t *data = (int8_t*)(0x08001000);

int main() {
    srand(0);
    for (int i = 0; i < NELEMENTS; ++i) {
        data[i * STEP] = (int8_t)(rand() % INT8_MAX);
    }

    srand(0);
    for (int i = 0; i < NELEMENTS; ++i) {
        assert(data[i * STEP] == (int8_t)(rand() % INT8_MAX));
    }

    return 0;
}