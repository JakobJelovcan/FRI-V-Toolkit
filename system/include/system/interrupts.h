#pragma once
#include <inttypes.h>

#define CSR_MIE_MSI (1 << 3)
#define CSR_MIE_MTI (1 << 7)
#define CSR_MIE_MEI (1 << 11)

#define CSR_MIP_MSI (1 << 3)
#define CSR_MIP_MTI (1 << 7)
#define CSR_MIP_MEI (1 << 11)

#define CSR_MSTATUS_MIE (1 << 3)

#define RISCV_INSTRUCTION_ADDRESS_MISALIGNED 0U
#define RISCV_INSTRUCTION_ACCESS_FAULT 1U
#define RISCV_ILLEGAL_INSTRUCTION 2U
#define RISCV_BREAKPOINT 3U
#define RISCV_LOAD_ADDRESS_MISALLIGNED 4U
#define RISCV_LOAD_ACCESS_FAULT 5U
#define RISCV_STORE_ADDRESS_MISALLIGNED 6U
#define RISCV_STORE_ACCESS_FAULT 7U
#define RISCV_MACHINE_ENVIROMENT_CALL 11U
#define RISCV_DIRECT_SOFTWARE_INTERRUPT 0x80000003U
#define RISCV_DIRECT_TIMER_INTERRUPT    0x80000007U
#define RISCV_DIRECT_EXTERNAL_INTERRUPT 0x8000000BU

#define BREAK asm("ebreak")
#define CALL asm("ecall")
#define MRET asm("mret")

__attribute__((always_inline)) static inline uint32_t csr_mstatus_write(uint32_t data) {
    volatile uint32_t res;
    asm("csrrw %0, mstatus, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mstatus_set(uint32_t data) {
    volatile uint32_t res;
    asm("csrrs %0, mstatus, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mstatus_clear(uint32_t data) {
    volatile uint32_t res;
    asm("csrrc %0, mstatus, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mstatus_read() {
    volatile uint32_t res;
    asm("csrrs %0, mstatus, x0" : "=r"(res));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mie_write(uint32_t data) {
    volatile uint32_t res;
    asm("csrrw %0, mie, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mie_set(uint32_t data) {
    volatile uint32_t res;
    asm("csrrs %0, mie, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mie_clear(uint32_t data) {
    volatile uint32_t res;
    asm("csrrc %0, mie, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mie_read() {
    volatile uint32_t res;
    asm("csrrs %0, mie, x0" : "=r"(res));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mtvec_write(uint32_t data) {
    volatile uint32_t res;
    asm("csrrw %0, mtvec, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mtvec_set(uint32_t data) {
    volatile uint32_t res;
    asm("csrrs %0, mtvec, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mtvec_clear(uint32_t data) {
    volatile uint32_t res;
    asm("csrrc %0, mtvec, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mtvec_read() {
    volatile uint32_t res;
    asm("csrrs %0, mtvec, x0" : "=r"(res));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mscratch_write(uint32_t data) {
    volatile uint32_t res;
    asm("csrrw %0, mscratch, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mscratch_set(uint32_t data) {
    volatile uint32_t res;
    asm("csrrs %0, mscratch, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mscratch_clear(uint32_t data) {
    volatile uint32_t res;
    asm("csrrc %0, mscratch, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mscratch_read() {
    volatile uint32_t res;
    asm("csrrs %0, mscratch, x0" : "=r"(res));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mepc_write(uint32_t data) {
    volatile uint32_t res;
    asm("csrrw %0, mepc, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mepc_set(uint32_t data) {
    volatile uint32_t res;
    asm("csrrs %0, mepc, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mepc_clear(uint32_t data) {
    volatile uint32_t res;
    asm("csrrc %0, mepc, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mepc_read() {
    volatile uint32_t res;
    asm("csrrs %0, mepc, x0" : "=r"(res));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mcause_write(uint32_t data) {
    volatile uint32_t res;
    asm("csrrw %0, mcause, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mcause_set(uint32_t data) {
    volatile uint32_t res;
    asm("csrrs %0, mcause, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mcause_clear(uint32_t data) {
    volatile uint32_t res;
    asm("csrrc %0, mcause, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mcause_read() {
    volatile uint32_t res;
    asm("csrrs %0, mcause, x0" : "=r"(res));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mtval_write(uint32_t data) {
    volatile uint32_t res;
    asm("csrrw %0, mtval, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mtval_set(uint32_t data) {
    volatile uint32_t res;
    asm("csrrs %0, mtval, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mtval_clear(uint32_t data) {
    volatile uint32_t res;
    asm("csrrc %0, mtval, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mtval_read() {
    volatile uint32_t res;
    asm("csrrs %0, mtval, x0" : "=r"(res));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mip_write(uint32_t data) {
    volatile uint32_t res;
    asm("csrrw %0, mip, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mip_set(uint32_t data) {
    volatile uint32_t res;
    asm("csrrs %0, mip, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mip_clear(uint32_t data) {
    volatile uint32_t res;
    asm("csrrc %0, mip, %1" : "=r"(res) : "r"(data));
    return res;
}

__attribute__((always_inline)) static inline uint32_t csr_mip_read() {
    volatile uint32_t res;
    asm("csrrs %0, mip, x0" : "=r"(res));
    return res;
}
