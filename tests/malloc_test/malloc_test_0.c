#include <inttypes.h>
#include <stdlib.h>
#include <system/interrupts.h>
#include <system/uart.h>
#include <system/assert.h>

#define NELEMENTS 64

volatile int data[NELEMENTS];

int main() {
    int* data = (int*) malloc(sizeof(int) * 100);

    for (int i = 0; i < 100; ++i) {
        data[i] = i;
    }

    for (int i = 0; i < 100; ++i) {
        assert(data[i] == i);
    }

    free(data);

    return 0;
}