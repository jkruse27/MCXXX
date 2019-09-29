.globl _start

# ------------------------------ Main ------------------------------------- #
_start:
  # ------------------- Leitura e Conversao da Entrada -------------------- #
  leitura:
    # Le o primeiro numero com sinal e guarda a conversao em s0 (Yb -> s0)
    jal ra, read_signal
    jal ra, read_unsigned_word
    jal ra, convert_unsigned
    jal ra, convert_word
    addi s0, a0, 0

    jal ra, descarta  # Descarta o espaco

    # Le o segundo numero com sinal e guarda a conversao em s1 (Xc -> s1)
    jal ra, read_signal
    jal ra, read_unsigned_word
    jal ra, convert_unsigned
    jal ra, convert_word
    addi s1, a0, 0

    jal ra, descarta  # Descarta o "\n"

    # Le o primeiro numero sem sinal e guarda a conversao em s2 (Ta -> s2)
    jal ra, read_unsigned_word
    jal ra, convert_unsigned
    addi s2, a0, 0

    jal ra, descarta  # Descarta o espaco

    # Le o primeiro numero com sinal e guarda a conversao em s3 (Tb -> s3)
    jal ra, read_unsigned_word
    jal ra, convert_unsigned
    addi s3, a0, 0

    jal ra, descarta  # Descarta o espaco

    # Le o primeiro numero com sinal e guarda a conversao em s4 (Tc -> s4)
    jal ra, read_unsigned_word
    jal ra, convert_unsigned
    addi s4, a0, 0

    jal ra, descarta  # Descarta o espaco

    # Le o primeiro numero com sinal e guarda a conversao em s5 (Tr -> s5)
    jal ra, read_unsigned_word
    jal ra, convert_unsigned
    addi s5, a0, 0

    jal ra, descarta  # Descarta o "\n"

    jal ra, get_distance  # substitui os tempos de cada satelite pela distancia

  # s0 = Yb, s1 = Xc, s2 = Da, s3 = Db, s4 = Dc

  # ---------------------------- Calculos --------------------------------- #
  calculos:
    encontra_y:
      mul a0, s0, s0
      mul a1, s2, s2
      add a0, a0, a1
      mul a1, s3, s3
      sub a0, a0, a1
      slli a1, s0, 1
      addi a2, a0, 0
      addi a3, a1, 0
      div a0, a0, a1
      jal ra, get_aprox
      add s9, a0, a4

    encontra_x:
      mul a2, s2, s2
      mul a1, a0, a0
      sub a0, a2, a1
      jal ra, raiz
    verifica_x:
      jal ra, find_right_x
      addi s10, a0, 0

      # s9 = y, s10 = x

  # ---------------------------- Imprimir --------------------------------- #
  imprimir:
    addi a0, s10, 0
    jal ra, get_ascii
    jal ra, print_num
    jal ra, print_space
    addi a0, s9, 0
    jal ra, get_ascii
    jal ra, print_num
    jal ra, print_line

  # ------------------------------ Sair ----------------------------------- #
  sair:
    li a0, 0 # exit code
    li a7, 93 # syscall exit
    ecall

# ---------------------------- Funcoes ------------------------------------ #
func:
  # Recebe uma palavra com sinal e deixa ela em number
  read_signal:
    li a0, 0        # file descriptor = stdin
    la a1, signal   #  buffer
    li a2, 1        # size
    li a7, 63       # syscall read
    ecall

    jalr x0, ra, 0  # Retorno

  # Recebe uma palavra sem sinal em deixa ela em unsigned_number
  read_unsigned_word:
    li a0, 0        # file descriptor = stdin
    la a1, unsigned_number   #  buffer
    li a2, 4        # size
    li a7, 63       # syscall read
    ecall


    jalr x0, ra, 0  # Retorno

  # Le e descarta \n ou Espaco
  descarta:
    li a0, 0        # file descriptor = stdin
    la a1, nothing  #  buffer
    li a2, 1        # size
    li a7, 63       # syscall read
    ecall

    jalr x0, ra, 0  # Retorno

  # Converte um numero com sinal em ascii em a0 e retorna ele em binario a0
  convert_word:
    #Verufica se o sinal e positivo ou negativo e, caso negativo, inverte o numero
    la t1, plus
    lw t1, 0(t1)
    la t6, signal
    lbu t0, 0(t6)
    beq t0, t1, retorno
    sub a0, x0, a0

    retorno:
      jalr x0, ra, 0

  # Converte um numero sem sinal em ascii em a0 e retorna ele em binario a0
  convert_unsigned:
    # Carrega constantes multiplicativas
    la t0, const_10
    la t1, const_100
    la t2, const_1000
    lw t0, 0(t0)
    lw t1, 0(t1)
    lw t2, 0(t2)

    # Carrega cada byte ascii do numero e subtrai 48 para obter o valor binario
    la tp, unsigned_number
    lbu a0, 0(tp)
    lbu t4, 1(tp)
    lbu t5, 2(tp)
    lbu t6, 3(tp)
    addi a0, a0, -48
    addi t4, t4, -48
    addi t5, t5, -48
    addi t6, t6, -48

    # Multiplica os numeros para obter o valor deles
    mul t5, t5, t0
    mul t4, t4, t1
    mul a0, a0, t2

    # Soma tudo em a0
    add a0, a0, t4
    add a0, a0, t5
    add a0, a0, t6

    # Retorno
    jalr x0, ra, 0

  # Pega os tempos em sX e muda eles pela distancia considerando que a
  # velocidade e 3*10^8 e o tempo esta em nanosegundos
  get_distance:
    li t0, 3
    li a3, 10

    #addi a2, s2, 0
    sub s2, s5, s2
    mul s2, s2, t0
    div s2, s2, a3
    #jal ra, get_aprox
    #add s2, s2, a4

    #addi a2, s3, 0
    sub s3, s5, s3
    mul s3, s3, t0
    div s3, s3, a3
    #jal ra, get_aprox
    #add s3, s3, a4

    #addi a2, s4, 0
    sub s4, s5, s4
    mul s4, s4, t0
    div s4, s4, a3
    #jal ra, get_aprox
    #add s4, s4, a4


    jalr x0, ra, 0

  # Verifica se a divisao de a2 por a3 deve ser aproximada pra cima ou pra baixo e
  # guarda em a4 o valor que deve ser adicionado ao numero para conseguir a aproximacao
  get_aprox:
    blt a3, x0, divisor_negativo
    blt a2, x0, dividido_negativo

    ambos_positivos:
      srli t5, a3, 1
      rem t6, a3, a2
      blt t6, t5, x0
      beq x0, x0, x1

    divisor_negativo:
      blt a3, x0, ambos_negativos
      beq x0, x0, dividido_negativo

    dividido_negativo:
      srli t5, a3, 1
      rem t6, a3, a2
      bge t6, t5, x0
      beq x0, x0, x_1

    ambos_negativos:
      beq x0, x0, ambos_positivos

    # Salva em a4 o valor que deve ser adicionado ao numero para arredondar
    x0:
      li a4, 0
      beq x0, x0, final
    x1:
      li a4, 1
      beq x0, x0, final
    x_1:
      li a4, -1
      beq x0, x0, final

    # Retorno
    final:
      jalr x0, ra, 0

  # Encontra a raiz positiva do numero em  a0 e retorna ela em a0
  raiz:
    li t6, 10
    # t0 = k, t1 = k', a0 = y, t6 = contador, t2 = temporaria
    srai t0, a0, 1
    loop:
      addi t6, t6, -1
      div t2, a0, t0
      add t1, t0, t2
      srai t0, t1, 1
      bne x0, t6, loop
    addi a0, t0, 0

    jalr x0, ra, 0

  # Verifca se x ou -x esta melhor resolve a equacao (x esta em a0 e a resposta sera colocada em ao)
  find_right_x:
    # Encontra o resultado da substituindo x na eq. 3 e deixa em t0
    sub t0, a0, s1
    mul t0, t0, t0
    addi t1, s9, 0
    mul t1, t1, t1
    add t0, t0, t1
    addi t1, s4, 0
    mul t1, t1, t1
    sub t0, t0, t1

    # Encontra o resultado da substituindo -x na eq. 3 e deixa em t1
    sub t3, x0, a0
    sub t1, t3, s1
    mul t1, t1, t1
    addi t2, s9, 0
    mul t2, t2, t2
    add t1, t1, t2
    addi t2, s4, 0
    mul t2, t2, t2
    sub t1, t1, t2

    blt x0, t0, next
    sub t0, x0, t0
    next:
      blt x0, t1, next_1
      sub t1, x0, t1
    next_1:
      blt t1, t0, negativo
      jalr x0, ra, 0
    negativo:
      sub a0, x0, a0
      jalr x0, ra, 0

    jalr x0, ra, 0

  # Encontra o ascii com sinal do valor em a0 e guarda os ascii em unsigned_number e signal
  get_ascii:
    la a2, signal
    la a7, unsigned_number
    blt a0, x0, change_signal
    la a3, plus
    beq x0, x0, continuing
    change_signal:
      la a3, minus
      sub a0, x0, a0
    continuing:
      lw a3, 0(a3)
      sb a3, 0(a2)

    la t0, const_1000
    lw t0, 0(t0)
    div a1, a0, t0
    addi a2, a1, 48
    sb a2, 0(a7)

    rem a0, a0, t0

    la t0, const_100
    lw t0, 0(t0)
    div a1, a0, t0
    addi a2, a1, 48
    sb a2, 1(a7)

    rem a0, a0, t0

    la t0, const_10
    lw t0, 0(t0)
    div a1, a0, t0
    addi a2, a1, 48
    sb a2, 2(a7)

    rem a0, a0, t0

    addi a2, a0, 48
    sb a2, 3(a7)

    jalr x0, ra, 0  # Retorno

  # Imprime numero com sinal
  print_num:
    li a0, 1        # file descriptor = stdout
    la a1, signal   #  buffer
    li a2, 1        # size
    li a7, 64       # syscall read
    ecall

    li a0, 1                  # file descriptor = stdout
    la a1, unsigned_number    #  buffer
    li a2, 4                  # size
    li a7, 64                 # syscall read
    ecall

    jalr x0, ra, 0  # Retorno

  # Imprime espaco
  print_space:
    li a0, 1        # file descriptor = stdout
    la a1, space    #  buffer
    li a2, 1        # size
    li a7, 64       # syscall read
    ecall

    jalr x0, ra, 0  # Retorno

  # Imprime new_line
  print_line:
    li a0, 1          # file descriptor = stdout
    la a1, new_line   #  buffer
    li a2, 1          # size
    li a7, 64         # syscall read
    ecall

    jalr x0, ra, 0  # Retorno

# --------------------- Constantes e Variaveis ---------------------------- #
const_var:
  #   Constantes para a conversao ascii
  const_10:
    .word 10
  const_100:
    .word 100
  const_1000:
    .word 1000

  # Plus character in ascii
  plus:
    .word 43

  # Minus character in ascii
  minus:
    .word 45

  # Space character in ascii
  space:
      .word 32

  # Caractere de nova linha em ascii
  new_line:
    .word 10

  # Espaco para armazenar temporariamente o numero com sinal lido da entrada
  signal:
    .skip 1

  # Espaco para armazenar temporariamente o numero sem sinal da entrada
  unsigned_number:
    .skip 4

  nothing:
    .skip 1
