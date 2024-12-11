#include <system/interrupts.h>

int main() {
    asm("ebreak");
    return 0;
}