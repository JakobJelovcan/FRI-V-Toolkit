#include <system/interrupts.h>

int main() {
    asm("li a0, 0x80000003");
    asm("csrrsi x0, mstatus, 0x8");
    asm("csrrsi x0, mie, 0x8");
    asm("csrrw x0, mcause, a0");
    asm("csrrsi x0, mip, 0x8");
    return 0;
}