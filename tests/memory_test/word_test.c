#include <system/assert.h>
#include <stdlib.h>

#define NELEMENTS 512
#define STEP 64

volatile int *data = (int*)(0x08001000);

int main() {
    srand(0);
    for (int i = 0; i < NELEMENTS; ++i) {
        data[i * STEP] = rand();
    }

    srand(0);
    for (int i = 0; i < NELEMENTS; ++i) {
        assert(data[i * STEP] == rand());
    }

    return 0;
}