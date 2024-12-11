
.globl _start
.type _start, @function

.weak riscv_mtvec_mei
.type riscv_mtvec_mei, @function

.weak riscv_mtvec_msi
.type riscv_mtvec_msi, @function

.weak riscv_mtvec_mti
.type riscv_mtvec_mti, @function

.local riscv_mtvec_table

.section .text.init.start
_start:
    # Initialize stack pointer
    la sp, _sp

    # Initialize interrupt vector table
    la t0, riscv_mtvec_table
    csrrw x0, mtvec, t0
    csrrsi x0, mtvec, 0x1
    li t0, 0x888
    csrrw x0, mie, t0
    csrrwi x0, mstatus, 0x8

    call init_memory

    call main

    # Return value from main should be in a0 (x10)

    # Infinite loop
1:
    j 1b

.section .text.interrupts.handlers
riscv_mtvec_msi:
1:
    j 1b

riscv_mtvec_mti:
1:
    j 1b

riscv_mtvec_mei:
1:
    j 1b

.section .text.interrupts.vector
riscv_mtvec_table:
    .org riscv_mtvec_table + 0*4
    jal zero, riscv_mtvec_exc

    .org riscv_mtvec_table + 3*4
    jal zero, riscv_mtvec_msi

    .org riscv_mtvec_table + 7*4
    jal zero, riscv_mtvec_mti

    .org riscv_mtvec_table + 11*4
    jal zero, riscv_mtvec_mei
