.section .text
.globl main
.type main, @function

.globl riscv_mtvec_msi
.type riscv_mtvec_msi, @function

main:
    csrrci zero, mie, (1 << 3)
    csrrsi zero, mip, (1 << 3)
    csrrci zero, mstatus, (1 << 3)
    csrrsi zero, mie, (1 << 3)
    mv a0, zero
    ret

riscv_mtvec_msi:
    ebreak
