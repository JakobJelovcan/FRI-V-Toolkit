.section .text
.globl main
.type main, @function

.globl riscv_mtvec_mti
.type riscv_mtvec_mti, @function

main:
    li t0, (1 << 7)
    li t1, 0x10000110
    csrrc zero, mie, t0
    sw zero, 8(t1)
    sw zero, 12(t1)
    csrrci zero, mstatus, (1 << 3)
    csrrs zero, mie, t0
    mv a0, zero
    ret

riscv_mtvec_mti:
    ebreak
