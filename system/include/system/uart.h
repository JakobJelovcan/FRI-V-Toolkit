#pragma once
#include <inttypes.h>
#include <stddef.h>

#define UART_BASE ((void*) 0x10000100)
#define UART_CR 0x0
#define UART_RX 0x4
#define UART_TX 0x8

#define UART_RXNE (0x1 << 2)
#define UART_TXE (0x1 << 1)
#define UART_EN (0x1 << 0)

#define UART_FREQ_MASK (0x7 << 3)
#define UART_FREQ_9600 (0x0 << 3)
#define UART_FREQ_19200 (0x1 << 3)
#define UART_FREQ_38400 (0x2 << 3)
#define UART_FREQ_57600 (0x3 << 3)
#define UART_FREQ_115200 (0x4 << 3)

#define UART_SIZE_MASK (0x7 << 6)
#define UART_SIZE_5 (0x0 << 6)
#define UART_SIZE_6 (0x1 << 6)
#define UART_SIZE_7 (0x2 << 6)
#define UART_SIZE_8 (0x3 << 6)
#define UART_SIZE_9 (0x4 << 6)
#define UART_RX_INT (0x1 << 9)
#define UART_TX_INT (0x1 << 10)

typedef struct {
    volatile uint32_t cr;
    volatile uint32_t rx;
    volatile uint32_t tx;
} uart_t;

typedef struct {
    char* rcv_ptr;
    volatile size_t rcv_count;
    const char* snd_ptr;
    volatile size_t snd_count;
} uart_control_t;

extern volatile uart_t* const uart;

uint8_t uart_receive();
void uart_transmit(uint8_t data);

void uart_transmit_str(const char* buf);
void uart_receive_str(char* buf, size_t count);

void uart_transmit_str_blocking(const char* buf);

void uart_cancel_transmit();
void uart_cancel_receive();

void uart_rx_callback();
void uart_tx_callback();

void uart_enable_IRQ();

void uart_transmit_done();
void uart_receive_done();

__attribute__((always_inline)) inline static void uart_enable() {
    uart->cr |= UART_EN;
}

__attribute__((always_inline)) inline static void uart_disable() {
    uart->cr &= ~UART_EN;
}

__attribute__((always_inline)) inline static void uart_init(uint32_t init) {
    uart->cr = init;
}

__attribute__((always_inline)) inline static uint32_t uart_get_freq() {
    return uart->cr & UART_FREQ_MASK;
}

__attribute__((always_inline)) inline static uint32_t uart_get_size() {
    return uart->cr & UART_SIZE_MASK;
}
