#pragma once
#include <inttypes.h>

#define PLIC_BASE ((void*) 0x10000000)
#define PLIC_PENDING 0x80
#define PLIC_ENABLED 0x84
#define PLIC_CLAIM 0x88
#define PLIC_CLEAR 0x8C

#define PLIC_UART_RX_IRQn 0x0
#define PLIC_UART_TX_IRQn 0x1

typedef struct {
    volatile uint32_t priority[32];
    volatile uint32_t pending;
    volatile uint32_t enabled;
    volatile uint32_t claim;
    volatile uint32_t clear;
} plic_t;

extern volatile plic_t* const plic;

__attribute__((always_inline)) inline static void plic_clear(uint32_t ext) {
    plic->clear = ext;
}

__attribute__((always_inline)) inline static uint32_t plic_claim() {
    return plic->claim;
}

__attribute__((always_inline)) inline static uint32_t plic_get_pending() {
    return plic->pending;
}

__attribute__((always_inline)) inline static void plic_enable_IRQ(uint32_t irqn) {
    plic->enabled |= (1 << irqn);
}

__attribute__((always_inline)) inline static void plic_set_priority(uint32_t irqn, uint32_t p) {
    plic->priority[irqn] = p;
}