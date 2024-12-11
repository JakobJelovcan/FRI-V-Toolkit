.section .text
.globl main
.type main, @function

main:
    li t0, 0x80000003
    csrrw zero, mcause, t0
    csrrci zero, mtvec, 0x3
    csrrsi zero, mip, (1 << 3)
    mv a0, zero
    ret
