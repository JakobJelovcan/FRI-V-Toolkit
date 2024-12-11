#include <inttypes.h>
#include <system/assert.h>
#include <stdlib.h>

#define NELEMENTS 512
#define STEP 64

volatile int16_t *data = (int16_t*)(0x08001000);

int main() {
    srand(0);
    for (int i = 0; i < NELEMENTS; ++i) {
        data[i * STEP] = (int16_t)(rand() % INT16_MAX);
    }

    srand(0);
    for (int i = 0; i < NELEMENTS; ++i) {
        assert(data[i * STEP] == (int16_t)(rand() % INT16_MAX));
    }

    return 0;
}