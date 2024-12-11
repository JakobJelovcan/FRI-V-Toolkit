#include <system/interrupts.h>

int main() {
    uint32_t* addr = (uint32_t*) 0x10001000;
    uint32_t x = *addr;
    asm("ebreak");
    asm("ebreak");
    asm("ebreak");
    asm("ebreak");

    return x;
}