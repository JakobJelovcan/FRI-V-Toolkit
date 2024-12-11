#include <ctype.h>
#include <stdbool.h>
#include <system/interrupts.h>
#include <system/plic.h>
#include <system/uart.h>

#define DATA_SIZE 32

void riscv_mtvec_mei(void) __attribute__((interrupt("machine")));

char snd_data[DATA_SIZE] = "Hello world!";
char rcv_data[DATA_SIZE] = {0};

volatile bool done = false;

int main() {
    uart_init(UART_FREQ_115200 | UART_SIZE_8 | UART_RX_INT | UART_TX_INT);
    uart_enable();
    uart_enable_IRQ();

    while (true) {
        uart_receive_str(rcv_data, DATA_SIZE);
        while (!done)
            ;
        done = false;

        for (int i = 0; i < DATA_SIZE; ++i) {
            if (isupper(rcv_data[i]))
                snd_data[i] = tolower(rcv_data[i]);
            else if (islower(rcv_data[i]))
                snd_data[i] = toupper(rcv_data[i]);
            else
                snd_data[i] = rcv_data[i];

            if (rcv_data[i] == '\0')
                break;
        }

        uart_transmit_str(snd_data);
    }

    return 0;
};

void riscv_mtvec_mei(void) {
    const uint32_t irqn = plic_claim();
    switch (irqn) {
        case 0:
            uart_rx_callback();
            break;
        case 1:
            uart_tx_callback();
            break;
        default:
            break;
    }

    csr_mip_clear(CSR_MIP_MEI);
    plic_clear(irqn);
}

void uart_receive_done() {
    done = true;
}