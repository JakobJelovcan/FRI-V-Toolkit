.section .text
.globl main
.type main, @function

main:
    li t0, 0x10
    li t1, 0x20
    add t0, t0, t1
    li t2, 0x30
    beq t2, t0, L0
    ebreak
L0:
    mv a0, zero
    ret
