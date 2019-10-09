.global ajudaORobinson

ajudaORobinson:
  li sp, 100000000
  jal inicializaVisitados

  # s0 = x do local
  # s1 = y do local
  jal posicaoXLocal
  mv s0, a0
  jal posicaoYLocal
  mv s1, a0

  # s2 = x atual
  # s3 = y atual
  jal posicaoYRobinson
  mv a1, a0
  mv s3, a0
  jal posicaoXRobinson
  mv s2, a0

  jal recursiva
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
    #ve se pode ir para x, y+1
    mv a0, s2
    addi a1, s3, 1
    jal daParaPassar
    beq a0, x0, next
    mv a0, s2
    addi a1, s3, 1
    jal foiVisitado
    mv a0, s2
    addi a1, s3, 1
    jal recursiva
    beq a0, x0, next
    j good_end

    next:
      #ve se pode ir para x+1, y+1
      addi a0, s2, 1
      addi a1, s3, 1
      jal daParaPassar
      beq a0, x0, next1
      addi a0, s2, 1
      addi a1, s3, 1
      jal foiVisitado
      bne a0, x0, next1
      addi a0, s2, 1
      addi a1, s3, 1
      jal recursiva
      beq a0, x0, next1
      j good_end

    next1:
      #ve se pode ir para x+1, y
      addi a0, s2, 1
      addi a1, s3, 0
      jal daParaPassar
      beq a0, x0, next2
      addi a0, s2, 1
      addi a1, s3, 0
      jal foiVisitado
      bne a0, x0, next2
      addi a0, s2, 1
      addi a1, s3, 0
      jal recursiva
      beq a0, x0, next2
      j good_end

    next2:
      #ve se pode ir para x+1, y-1
      addi a0, s2, 1
      addi a1, s3, -1
      jal daParaPassar
      beq a0, x0, next3
      addi a0, s2, 1
      addi a1, s3, -1
      jal foiVisitado
      bne a0, x0, next3
      addi a0, s2, 1
      addi a1, s3, -1
      jal recursiva
      beq a0, x0, next3
      j good_end

    next3:
      #ve se pode ir para x, y-1
      addi a0, s2, 0
      addi a1, s3, -1
      jal daParaPassar
      beq a0, x0, next4
      addi a0, s2, 0
      addi a1, s3, -1
      jal foiVisitado
      bne a0, x0, next4
      addi a0, s2, 0
      addi a1, s3, -1
      jal recursiva
      beq a0, x0, next4
      j good_end

    next4:
      #ve se pode ir para x-1, y-1
      addi a0, s2, -1
      addi a1, s3, -1
      jal daParaPassar
      beq a0, x0, next5
      addi a0, s2, -1
      addi a1, s3, -1
      jal foiVisitado
      bne a0, x0, next5
      addi a0, s2, -1
      addi a1, s3, -1
      jal recursiva
      beq a0, x0, next5
      j good_end

    next5:
      #ve se pode ir para x-1, y
      addi a0, s2, -1
      addi a1, s3, 0
      jal daParaPassar
      beq a0, x0, next6
      addi a0, s2, -1
      addi a1, s3, 0
      jal foiVisitado
      bne a0, x0, next6
      addi a0, s2, -1
      addi a1, s3, 0
      jal recursiva
      beq a0, x0, next6
      j good_end

    next6:
      #ve se pode ir para x-1, y+1
      addi a0, s2, -1
      addi a1, s3, 1
      jal daParaPassar
      beq a0, x0, ok_end
      addi a0, s2, -1
      addi a1, s3, 1
      jal foiVisitado
      bne a0, x0, ok_end
      addi a0, s2, -1
      addi a1, s3, 1
      jal recursiva
      beq a0, x0, ok_end
      j good_end


  #Nenhum caminho e possivel a partir desse no
  ok_end:
    mv a0, s2
    mv a1, s3
    jal foiVisitado

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
