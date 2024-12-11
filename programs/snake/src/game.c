#include <ctype.h>
#include <snake/snake.h>
#include <stdbool.h>
#include <system/interrupts.h>
#include <system/plic.h>
#include <system/time.h>
#include <system/uart.h>
#include <system/uprintf.h>

#define LOOP_TIME (CLOCKS_PER_SEC)
#define SPEED_FACTOR (CLOCKS_PER_SEC / 100)

void riscv_mtvec_mei(void) __attribute__((interrupt("machine")));
void riscv_mtvec_mti(void) __attribute__((interrupt("machine")));

game_t game;

int main() {
    uart_init(UART_FREQ_115200 | UART_SIZE_8 | UART_RX_INT);
    uart_enable();
    uart_enable_IRQ();

    initialize(&game);
    mtimer_set_raw_time_cmp(LOOP_TIME);
    while (true)
        ;
    return 0;
}

void riscv_mtvec_mti(void) {
    const uint64_t start = mtimer_get_raw_time();
    update_snake(&game);
    const void* buff = draw(&game);
    const uint64_t end = mtimer_get_raw_time();
    const uint64_t diff = end - start;
    mtimer_set_raw_time_cmp(LOOP_TIME - game.apple_count * SPEED_FACTOR);

    uart_transmit_str_blocking(buff);
    if (!game.game_over && !game.game_paused) {
        uprintf("Apples eaten: %d\n", game.apple_count);
        uprintf("Loop time: %u\n", (uint32_t) diff);
    }
}

void riscv_mtvec_mei(void) {
    const uint32_t irqn = plic_claim();
    switch (irqn) {
        case 0:
            process_input(&game, uart->rx);
            break;
        default:
            break;
    }

    csr_mip_clear(CSR_MIP_MEI);
    plic_clear(irqn);
}