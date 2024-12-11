.section .text
.globl main
.type main, @function

main:
    li t0, 0x10
    li t1, 0x20
    li t0, 0x20
    sub t0, t1, t0
    beq zero, t0, L0
    ebreak
L0:
    mv a0, zero
    ret
