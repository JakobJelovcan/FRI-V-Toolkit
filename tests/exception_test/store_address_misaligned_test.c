#include <system/interrupts.h>

int main() {
    uint32_t* addr = (uint32_t*) 0x100001;
    uint32_t x = 10;
    asm("sw %0, 0(%1)" : : "r"(x), "r"(addr));
    asm("ebreak");
    asm("ebreak");
    asm("ebreak");

    return 0;
}