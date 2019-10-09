.global ajudaORobinson

ajudaORobinson:
  li sp, 100000000
  mv s6, ra
  jal inicializaVisitados
  mv ra, s6

  # s0 = x do local
  # s1 = y do local
  mv s6, ra
  jal posicaoXLocal
  mv ra, s6
  mv s0, a0
  mv s6, ra
  jal posicaoYLocal
  mv ra, s6
  mv s1, a0

  # s2 = x atual
  # s3 = y atual
  mv s6, ra
  jal posicaoYRobinson
  mv ra, s6
  mv a1, a0
  mv s3, a0
  mv s6, ra
  jal posicaoXRobinson
  mv ra, s6
  mv s2, a0

  mv s6, ra
  jal recursiva
  mv ra, s6
  beq a0, x0, bad_end
  j real_end

  # Retorna a funcao quando nao for possivel ir para lugar nenhum mais
  bad_end:
    li a0, 1
    la a1, string
    li a2, 23
    li a7, 64
    ecall

  real_end:
    ret

# Funcao que fara a busca
# Retorna 0 se nao tiver caminho e 1 se tiver caminho
recursiva:
  addi sp, sp, -12
  sw ra, 8(sp)
  sw s2, 4(sp)
  sw s3, 0(sp)

  mv s2, a0
  mv s3, a1

  bne s2, s0, lops
  bne s1, s3, lops
  j good_end

  lops:
    li t3, 1
    li t0, -1
    li t2, 2
    for_x:
      beq t0, t2, ok_end
      li t1, -1
      for_y:
        beq t3, t1, x_1
        code:
          add a0, s2, t0
          add a1, s3, t1
          mv s6, ra
          jal daParaPassar
          mv ra, s6
          beq a0, x0, final
          add a0, s2, t0
          add a1, s3, t1
          mv s6, ra
          jal foiVisitado
          mv ra, s6
          add a0, s2, t0
          add a1, s3, t1
          mv s6, ra
          jal recursiva
          mv ra, s6
          beq a0, x0, final
          j good_end
        x_1:
          beq t1, t3, final
          j code
        final:
          addi t1, t1, 1
          bne t1, t2, for_y
          addi t0, t0, 1
          j for_x

  #Nenhum caminho e possivel a partir desse no
  ok_end:
    mv a0, s2
    mv a1, s3
    mv s6, ra
    jal foiVisitado
    mv ra, s6

    mv a0, x0

    lw ra, 8(sp)
    lw s2, 4(sp)
    lw s3, 0(sp)
    addi sp, sp, 12

    ret

  # Imprime a posicao atual e retorna a funcao quando se chega ao final do camiho certo
  good_end:
    addi s2, s2, 48
    addi s3, s3, 48
    la t0, y_atual
    sw s3, 0(t0)
    la t0, x_atual
    sw s2, 0(t0)

    li a0, 1
    la a1, x_atual
    li a2, 1
    li a7, 64
    ecall

    li a0, 1
    la a1, space
    li a2, 1
    li a7, 64
    ecall

    li a0, 1
    la a1, y_atual
    li a2, 1
    li a7, 64
    ecall

    li a0, 1
    la a1, new_line
    li a2, 1
    li a7, 64
    ecall

    lw ra, 8(sp)
    lw s2, 4(sp)
    lw s3, 0(sp)
    addi sp, sp, 12

    ret

space:  .word 32
new_line: .word 10
x_atual: .skip 4
y_atual: .skip 4
string: .asciz "Não existe um caminho!\n"
