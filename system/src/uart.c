#include <string.h>
#include <system/plic.h>
#include <system/uart.h>

volatile uart_t* const uart = (uart_t*) UART_BASE;
volatile uart_control_t uart_control = {NULL, 0, NULL, 0};

void uart_enable_IRQ() {
    plic_enable_IRQ(PLIC_UART_RX_IRQn);
    plic_enable_IRQ(PLIC_UART_TX_IRQn);
    plic_set_priority(PLIC_UART_RX_IRQn, 10);
    plic_set_priority(PLIC_UART_TX_IRQn, 10);
}

void uart_cancel_transmit() {
    uart_control.snd_count = 0;
    uart_control.snd_ptr = NULL;
}

void uart_cancel_receive() {
    uart_control.rcv_count = 0;
    uart_control.rcv_ptr = NULL;
}

__attribute__((weak)) void uart_transmit_done() {
    // Weak function
    // Redefine
    return;
}

__attribute__((weak)) void uart_receive_done() {
    // Weak function
    // Redefine
    return;
}

void uart_transmit_str(const char* buf) {
    while (uart_control.snd_count != 0)
        ;

    uart_control.snd_ptr = buf;
    uart_control.snd_count = strlen(buf) + 1;

    uart_tx_callback();
}

void uart_transmit_str_blocking(const char* buf) {
    const uint32_t len = strlen(buf);
    for (int i = 0; i <= len; ++i) {
        uart_transmit(buf[i]);
    }
}

void uart_receive_str(char* buf, size_t count) {
    while (uart_control.rcv_count != 0)
        ;

    uart_control.rcv_ptr = buf;
    uart_control.rcv_count = count;
}

void uart_rx_callback() {
    const char chr = uart_receive();

    if (chr == 0x00 || chr == 0x04 || chr == '\n' || uart_control.rcv_count == 1) {
        *uart_control.rcv_ptr = '\0';
        uart_control.rcv_ptr = NULL;
        uart_control.rcv_count = 0;
        uart_receive_done();
    } else {
        *uart_control.rcv_ptr = chr;
        ++uart_control.rcv_ptr;
        --uart_control.rcv_count;
    }
}

void uart_tx_callback() {
    if (uart_control.snd_count == 0) {
        uart_control.snd_ptr = NULL;
        uart_transmit_done();
    } else {
        uart_transmit(*uart_control.snd_ptr);
        ++uart_control.snd_ptr;
        --uart_control.snd_count;
    }
}

void uart_transmit(uint8_t data) {
    while (!(uart->cr & UART_TXE))
        ;
    uart->tx = data;
}

uint8_t uart_receive() {
    while (!(uart->cr & UART_RXNE))
        ;
    return uart->rx;
}
