#include <inttypes.h>
#include <system/assert.h>
#include <stdlib.h>

#define NELEMENTS 512
#define STEP 64

volatile uint8_t *data = (uint8_t*)(0x08001000);

int main() {
    srand(0);
    for (int i = 0; i < NELEMENTS; ++i) {
        data[i * STEP] = (uint8_t)(rand() % UINT8_MAX);
    }

    srand(0);
    for (int i = 0; i < NELEMENTS; ++i) {
        assert(data[i * STEP] == (uint8_t)(rand() % UINT8_MAX));
    }

    return 0;
}