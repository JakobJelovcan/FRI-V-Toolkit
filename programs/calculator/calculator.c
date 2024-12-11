#include <calclib/lex.h>
#include <calclib/parse.h>
#include <ctype.h>
#include <stdbool.h>
#include <system/interrupts.h>
#include <system/plic.h>
#include <system/uart.h>
#include <system/uprintf.h>

#define DATA_SIZE 64

void riscv_mtvec_mei(void) __attribute__((interrupt("machine")));

char str[DATA_SIZE] = {0};
token_t tokens[DATA_SIZE] = {0};

volatile bool done = false;

int main() {
    uart_init(UART_FREQ_115200 | UART_SIZE_8 | UART_RX_INT);
    uart_enable();
    uart_enable_IRQ();

    while (true) {
        uart_receive_str(str, DATA_SIZE);
        while (!done)
            ;
        done = false;

        int res = scan(str, tokens, DATA_SIZE);
        if (res == LEX_INVALID_TOKEN) {
            uprintf("Invalid token\n");
            continue;
        } else if (res == LEX_OUT_OF_SPACE) {
            uprintf("Out of space\n");
            continue;
        }

        const int32_t result = evaluate(tokens);

        if (parser_errno == PARSER_UNEXPECTED_TOKEN) {
            uprintf("Unexpected token\n");
            continue;
        }

        uprintf("%d\n", result);
    }

    return 0;
};

void riscv_mtvec_mei(void) {
    const uint32_t irqn = plic_claim();
    switch (irqn) {
        case 0:
            uart_rx_callback();
            break;
        default:
            break;
    }

    csr_mip_clear(CSR_MIP_MEI);
    plic_clear(irqn);
}

void riscv_division_by_zero_handler(void) {
    uprintf("Division by zero\n");
    for (;;)
        ;
}

void uart_receive_done() {
    done = true;
}