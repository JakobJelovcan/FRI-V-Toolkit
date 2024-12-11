#include <system/interrupts.h>

int main() {
    void* addr = (void*) 0x10000000;

    asm("jalr x0, %0" : : "r"(addr));
    return 0;
}