#include <system/interrupts.h>

int main() {
    void* addr = (void*) 0x100001;
    uint32_t x;
    asm("lw %0, 0(%1)" : "=r"(x) : "r"(addr));
    asm("ebreak");
    asm("ebreak");
    asm("ebreak");
    asm("ebreak");

    return x;
}
