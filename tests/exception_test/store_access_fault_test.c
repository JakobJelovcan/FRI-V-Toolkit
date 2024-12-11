#include <system/interrupts.h>

int main() {
    uint32_t* addr = (uint32_t*) 0x10001000;
    *addr = 10;
    asm("ebreak");
    asm("ebreak");
    asm("ebreak");
    asm("ebreak");

    return 0;
}