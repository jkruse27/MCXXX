.globl _start

_start:
    li a0, 0      # file descriptor = stdin
    la a1, l1     #  buffer
    li a2, 12     # size
    li a7, 63     # syscall read
    ecall

    li a0, 0      # file descriptor = stdin
    la a1, l2     #  buffer
    li a2, 20     # size
    li a7, 63     # syscall read
    ecall

    la a0, l1     # Conversao da linha
    li a1, 1   # Constante 10
    li a2, 10   # Constante 100
    li a3, 100   # Constante 1000
    li a4, 1000  # Constante 10000

    #Converte o numero para binario
    lbu t1, 1(a0)
    addi t1, t1, -48
    mul t0, t1, a4

    lbu t1, 2(a0)
    addi t1, t1, -48
    mul t1, t1, a3
    add t0, t0, t1

    lbu t1, 3(a0)
    addi t1, t1, -48
    mul t1, t1, a2
    add t0, t0, t1

    lbu t1, 4(a0)
    addi t1, t1, -48
    mul t1, t1, a1
    add t0, t0, t1

    slli t0, t0, 2
    sw t0, 0(a0)

    li a0, 1 # file descriptor = stdout
    la a1, l1 #  buffer
    li a2, 5 # size
    li a7, 64 # syscall write
    ecall

    li a0, 1 # file descriptor = stdout
    la a1, new_line #  buffer
    li a2, 1 # size
    li a7, 64 # syscall write
    ecall
    #
    # li a0, 1 # file descriptor = stdout
    # la a1, string2 #  buffer
    # li a2, 20 # size
    # li a7, 64 # syscall write
    # ecall

    li a0, 0 # exit code
    li a7, 93 # syscall exit
    ecall

l1:   # First line
  .skip 12

l2:   # Second line
  .skip 20

new_line:
  .word 10
