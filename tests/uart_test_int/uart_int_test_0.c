#include <stdbool.h>
#include <system/interrupts.h>
#include <system/plic.h>
#include <system/uart.h>

volatile uint8_t receive = 0;
volatile bool wait = true;

void riscv_mtvec_mei(void) __attribute__((interrupt("machine")));

int main() {
    plic_enable_IRQ(PLIC_UART_RX_IRQn);
    plic_set_priority(PLIC_UART_RX_IRQn, 31);
    uart_init(UART_FREQ_115200 | UART_SIZE_8 | UART_RX_INT | UART_TX_INT);
    uart_enable();

    uart_transmit('A');

    while (wait)
        ;

    if (receive == 'A')
        return 0;
    else
        return 1;
}

void riscv_mtvec_mei(void) {
    uint32_t claim = plic_claim();
    receive = uart_receive();
    wait = false;
    csr_mip_clear(CSR_MIP_MEI);
    plic_clear(claim);
}