.section .text
.globl main
.type main, @function

.globl riscv_mtvec_mei
.type riscv_mtvec_mei, @function

main:
    sw ra, 0(sp)
    addi sp, sp, -4
    li t4, (1 << 11)
    li t1, 0x10000100
    csrrc zero, mie, t4
    call init_uart
    call init_plic
    call send_uart

    li t0, 0x800
L0:
    addi t0, t0, -1
    bne zero, t0, L0

    csrrci zero, mstatus, (1 << 3)
    csrrs zero, mie, t4

    lw ra, 4(sp)
    addi sp, sp, 4

    mv a0, zero
    ret

init_uart:
    li t0, 0x10000100
    li t1, 0x6E1
    sw t1, 0(t0)
    ret

init_plic:
    li t0, 0x10000000
    li t1, 0x1F
    sw t1, 0(t0)
    sw t1, 4(t0)
    li t1, 0x3
    sw t1, 0x84(t0)
    ret

send_uart:
    li t0, 0x10000100
    li t1, 0xAA
    sw t1, 8(t0)
    ret

riscv_mtvec_mei:
    ebreak
