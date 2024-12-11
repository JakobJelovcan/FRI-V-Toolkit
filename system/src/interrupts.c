#include <system/interrupts.h>

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_instruction_address_misaligned_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_instruction_access_fault_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_illegal_instruction_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_breakpoint_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_load_address_misaligned_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_load_access_fault_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_store_address_misaligned_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_store_access_fault_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_machine_enviroment_call_handler(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_direct_external_interrupt(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_direct_software_interrupt(void) {
    for (;;)
        ;
}

__attribute__((section(".text.interrupts.handlers"), weak)) void riscv_direct_timer_interrupt(void) {
    for (;;)
        ;
}

__attribute__((interrupt("machine"))) void riscv_mtvec_exc(void) {
    uint32_t cause = csr_mcause_read();

    switch (cause) {
        case RISCV_INSTRUCTION_ADDRESS_MISALIGNED:
            riscv_instruction_address_misaligned_handler();
            break;
        case RISCV_INSTRUCTION_ACCESS_FAULT:
            riscv_instruction_access_fault_handler();
            break;
        case RISCV_ILLEGAL_INSTRUCTION:
            riscv_illegal_instruction_handler();
            break;
        case RISCV_BREAKPOINT:
            riscv_breakpoint_handler();
            break;
        case RISCV_LOAD_ADDRESS_MISALLIGNED:
            riscv_load_address_misaligned_handler();
            break;
        case RISCV_LOAD_ACCESS_FAULT:
            riscv_load_access_fault_handler();
            break;
        case RISCV_STORE_ADDRESS_MISALLIGNED:
            riscv_store_address_misaligned_handler();
            break;
        case RISCV_STORE_ACCESS_FAULT:
            riscv_store_access_fault_handler();
            break;
        case RISCV_MACHINE_ENVIROMENT_CALL:
            riscv_machine_enviroment_call_handler();
            break;
        case RISCV_DIRECT_EXTERNAL_INTERRUPT:
            riscv_direct_external_interrupt();
            break;
        case RISCV_DIRECT_SOFTWARE_INTERRUPT:
            riscv_direct_software_interrupt();
            break;
        case RISCV_DIRECT_TIMER_INTERRUPT:
            riscv_direct_timer_interrupt();
            break;
        default:
            break;
    }

    csr_mip_clear(CSR_MIP_MSI);
}