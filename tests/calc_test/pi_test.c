#include <stdlib.h>
#include <inttypes.h>
#include <system/assert.h>

#define N 1000

int main() {
    srand(0);
    uint32_t count = 0;
    for (uint32_t i = 0; i < N; ++i) {
        const float x = rand() / (float)RAND_MAX;
        const float y = rand() / (float)RAND_MAX;
        if (x * x + y * y <= 1.0f) {
            ++count;
        }
    }

    const float pi = 4.0f * count / (float)N;
    assert(3.0f < pi && pi < 3.3);
    return 0;
}