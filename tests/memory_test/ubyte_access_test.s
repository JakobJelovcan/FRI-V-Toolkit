.section .text
.globl main
.type main, @function

main:
    li t0, 0x11223344
    li t1, 0x08001000
    sw t0, 0(t1)
    li t0, 0x8008F07A
    li t2, 0x08005000
    sw t0, 0(t2)

    lbu t3, 0(t1)
    li t4, 0x44
    beq t3, t4, L0
    ebreak

L0:
    lbu t3, 1(t1)
    li t4, 0x33
    beq t3, t4, L1
    ebreak

L1:
    lbu t3, 2(t1)
    li t4, 0x22
    beq t3, t4, L2
    ebreak

L2:
    lbu t3, 3(t1)
    li t4, 0x11
    beq t3, t4, L3
    ebreak

L3: 
    lbu t3, 0(t2)
    li t4, 0x7A
    beq t3, t4, L4
    ebreak

L4: 
    lbu t3, 1(t2)
    li t4, 0xF0
    beq t3, t4, L5
    ebreak

L5: 
    lbu t3, 2(t2)
    li t4, 0x08
    beq t3, t4, L6
    ebreak

L6:
    lbu t3, 3(t2)
    li t4, 0x80
    beq t3, t4, L7
    ebreak

L7:
    mv a0, zero
    ret
