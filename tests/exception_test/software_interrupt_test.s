.section .text
.globl main
.type main, @function

main:
    csrrci x0, mstatus, 0x8
    csrrsi x0, mie, 0x8

    li a0, 0x10000118
    sw x0, 0(a0)
    sw x0, 4(a0)

    li a0, 0x80000003
    csrrw x0, mcause, a0
    csrrsi x0, mip, 0x8
    csrrsi x0, mstatus, 0x8
