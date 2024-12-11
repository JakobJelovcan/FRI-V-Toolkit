.section .text
.globl main
.type main, @function

main:
    li t0, (1 << 7)
    li t1, 0x10000110
    csrrs zero, mie, t0
    csrrci zero, mtvec, 0x3
    sw zero, 8(t1)
    sw zero, 12(t1)
    mv a0, zero
    ret
