.section .text
.globl main
.type main, @function

main:
    li t0, 0x1
    add t0, t0, t0
    add t0, t0, t0
    add t0, t0, t0
    add t0, t0, t0
    li t1, 0x10
    beq t1, t0, L0
    ebreak
L0:
    mv a0, zero
    ret
