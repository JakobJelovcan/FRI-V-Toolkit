#include <system/uart.h>
#include <system/assert.h>

int main() {
    uart->cr = UART_SIZE_8 | UART_FREQ_115200;
    assert((uart->cr & (UART_SIZE_MASK | UART_FREQ_MASK)) == (UART_SIZE_8 | UART_FREQ_115200));
    uart->cr |= UART_EN;
    uart->cr = (uart->cr & ~(UART_SIZE_MASK | UART_FREQ_MASK)) | (UART_SIZE_6 | UART_FREQ_38400);
    assert((uart->cr & (UART_SIZE_MASK | UART_FREQ_MASK)) == (UART_SIZE_8 | UART_FREQ_115200));
    uart->cr = UART_FREQ_57600 | UART_SIZE_7;
    assert((uart->cr & (UART_SIZE_MASK | UART_FREQ_MASK)) == (UART_FREQ_57600 | UART_SIZE_7));
    return 0;
}