.section .text
.globl main
.type main, @function

main:
    li t0, 0x142383A4
    li t1, 0x08001000
    sw t0, 0(t1)
    li t0, 0x8078E09A
    li t2, 0x08005000
    sw t0, 0(t2)

    lh t3, 0(t1)
    li t4, 0xFFFF83A4
    beq t3, t4, L0
    ebreak

L0:
    lh t3, 2(t1)
    li t4, 0x1423
    beq t3, t4, L1
    ebreak

L1:
    lh t3, 0(t2)
    li t4, 0xFFFFE09A
    beq t3, t4, L2
    ebreak

L2:
    lh t3, 2(t2)
    li t4, 0xFFFF8078
    beq t3, t4, L3
    ebreak

L3:
    mv a0, zero
    ret
