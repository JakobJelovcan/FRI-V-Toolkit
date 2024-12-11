#include <stdbool.h>
#include <system/interrupts.h>
#include <system/time.h>

volatile bool wait = true;

int main() {
    mtimer_set_raw_time_cmp(1000);
    while (wait)
        ;

    wait = false;
    mtimer_set_raw_time_cmp(1000);
    while (wait)
        ;

    return 0;
}

__attribute__((interrupt("machine"))) void riscv_mtvec_mti(void) {
    mtimer_set_raw_time_cmp(1000000);
    wait = false;
}