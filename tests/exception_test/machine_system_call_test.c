#include <system/interrupts.h>

int main() {
    asm("ecall");
    return 0;
}
