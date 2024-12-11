#include <system/interrupts.h>

int main() {
    volatile uint32_t* ptr = (volatile uint32_t*) 0x0000000C;
    *ptr = 10;
    ptr = (volatile uint32_t*) 0x08000000;
    return *ptr;
}