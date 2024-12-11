#include <system/interrupts.h>
#include <system/uart.h>
#include <system/assert.h>

int main() {
    uart_init(UART_FREQ_115200 | UART_SIZE_8);
    uart_enable();

    uart_transmit('A');
    uint8_t rec = uart_receive();
    assert(rec == 'A');
}