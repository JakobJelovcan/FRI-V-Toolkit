.section .text
.globl main
.type main, @function

main:
    mv t0, zero
    li t1, 0x10
    mv zero, t1
    beq t0, zero, L0
    ebreak
L0:
    mv a0, zero
    ret
