#include <system/interrupts.h>
#include <system/plic.h>

int main() {
    plic->pending = 0;
    return 0;
}
