.section .text
.globl main
.type main, @function

main:
    li t0, 0x08001000
    li t1, 0x30
    sw t1, 0(t0)
    li t1, -0x30
    lw t2, 0(t0)
    add t0, t1, t2
    beq zero, t0, L0
    ebreak
L0:
    mv a0, zero
    ret
