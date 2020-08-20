.globl _start

# Função para obtenção do tempo atual. ao <= tempo atual
time_now:
  la a0, buffer_timeval
  la a1, buffer_timerzone
  li a7, 169 # chamada de sistema gettimeofday
  ecall
  la a0, buffer_timeval
  lw t1, 0(a0) # tempo em segundos
  lw t2, 8(a0) # fração do tempo em microssegundos
  li t3, 1000
  mul t1, t1, t3
  div t2, t2, t3
  add a0, t2, t1
  ret

# Função para tocar o canal a0 canal do sintetizador
play_channel:
  slli a1, a0, 2     # canal = canal*4 // calcula posicao do canal no vetor C
  add a7, s8, a1     # soma deslocamento na matriz M
  add a4, s4, a1     # soma deslocamento no vetor P
  add a5, s5, a1     # soma deslocamento no vetor P2
  add a3, s3, a1     # soma deslocamento no vetor C
  lw t1, 0(a7)       # lê matriz
  srli t2, t1, 16    # t2 = frequencia||velocidade
  beq t2, zero, end  # se zero, não tocar nada
  lw t3, 0(a4)       # t3 = (frequencia||velocidade) tocadas por último
  bne t2, t3, tocar; # se diferente, trocou a nota, então deve tocar
  lw t3, 0(a5)       # Tempo de termino do que está tocando
  ble s7, t3, end;   # Se ainda não parou de tocar anterior, não deve tocar novamente
  tocar:
    sw t2, 0(a4)     # Atualiza (frequencia||velocidade) em P
    and t2, t1, s6   # t2 = delay
    add t2, t2, s7   # Calcula até quando ir tocar
    sw t2, 0(a5)     # Armazena no vetor P2
    mv a2, a0        # Define o Canal
    lw a0, 0(a3)     # Carrega instrumento do canal
    mv a1, t1        # move (frequencia||velocidade||delay) para a1
    li a7, 2048      # chamada de sistema
    ecall
  end:
    ret

# Função para tocar todos os canais do sintetizador
play_all_channels:
  li a0, 15
  mv s10, ra
  while_channels:
    mv s9, a0
    jal play_channel
    add a0, s9, -1
    bge a0, zero, while_channels
  mv ra, s10
  ret

# Recebe um numero e transforma em binario salvo em a0, se for seguido de espaco deixa
# em a1 1 e se for seguido de \n deixa em a1 0
receive_number:
  loops1:
    li a0, 0
    la a1, char
    li a2, 1
    li a7, 63
    ecall

    lbu t1, 0(a1)

    li t2, 32
    beq t1, t2, end6
    li t2, 10
    beq t1, t2, end7

    addi t1, t1, -48

    mul t3, t3, t2
    add t3, t3, t1
    j loops1

  end6:
    mv a0, t3
    li a1, 1
    jalr x0, sp, 0
  end7:
    mv a0, t3
    li a1, 0
    jalr x0, sp, 0

# Ignora toda a linha do head
ignore_head:
  loop:
    li a0, 0
    la a1, char
    li a2, 1
    li a7, 63
    ecall

    lbu a3, 0(a1)
    li s0, 10
    bne a3, s0, loop  # se a letra for \n, sai do loop

  jalr x0, tp, 0

# Ignora a palavra Program
ignore_program:
  jal sp, receive_number
  li a0, 0
  la a1, char
  li a2, 1
  li a7, 63
  ecall
  li a0, 0
  la a1, char
  li a2, 1
  li a7, 63
  ecall
  jalr x0, tp, 0

# Trata cada linha dependendo do caso
get_program:
  li a0, 0          # stdin
  la a1, char       # discards
  li a2, 1          # size 1
  li a7, 63         # syscall read
  ecall

  la t0, char
  lbu t0, 0(t0)

  li t1, 72         # Se a letra for "h" indica que e um head
  beq t0, t1, h
  li t1, 80         # Se a letra for "p" indica que e um program
  beq t0, t1, p
  n:
    la s0, linha

    la s1, ticks
    lw s1, 0(s1)

    la s2, bpm
    lw s2, 0(s2)

    li s3, 10
    div s1, s1, s3
    li s3, 6000
    mv t3, t0
    addi t3, t3, -48

    #Recebe o primeiro numero, converte e salva
    jal sp, receive_number
    beq x0, a1, end5
    mul a0, a0, s3
    div a0, a0, s1
    div a0, a0, s2
    sw a0, 0(s0)
    addi s0, s0, 4

    #Recebe o segundo numero, converte e salva
    li t3, 0
    jal sp, receive_number
    li t3, 0
    mul a0, a0, s3
    div a0, a0, s1
    div a0, a0, s2
    sw a0, 0(s0)
    addi s0, s0, 4

    loops:
      jal sp, receive_number
      li t3, 0
      sw a0, 0(s0)
      addi s0, s0, 4
      bne a1, x0, loops

    continue:
      la t0, linha
      la t1, M
      lw a0, 0(t0)      #t inicial (t atual)
      mv a2, a0
      lw a1, 4(t0)      #t final
      lw s0, 12(t0)     #canal
      addi s0, s0, -1
      slli s0, s0, 2
      lw s1, 16(t0)     #f
      lw s2, 20(t0)     #v

      slli s1, s1, 24
      slli s2, s2, 16
      slli a0, a0, 6
      add a0, a0, t1

      add a0, a0, s0
      or s3, s1, s2

      loopi:
        sub a3, a1, a2
        or s4, s3, a3
        sw s4, 0(a0)
        addi a2, a2, 1
        addi a0, a0, 64
        bge a1, a2, loopi
      sw s4, 0(a0)
      j end1

  end5:
    li a0, 0
    ret

  h:
    jal tp, ignore_head
    j end1
  p:
    jal tp, ignore_program
    li t3, 0
    jal sp, receive_number
    li t3, 0

    mv s0, a0
    jal sp, receive_number
    li t3, 0

    li a0, 0
    la a1, char
    li a2, 1
    li a7, 63
    ecall

    line_end:               # Quando chega no final da linha, adiciona o intrumento na faixa da lista C
      la t0, C              # Endereco de C
      addi s0, s0, -1
      slli s0, s0, 2        # Adiciona a 4*(faixa - 1) e depois soma com a posicao inicial para achar a posicao do vetor
      add t0, t0, s0
      sw a0, 0(t0)          # Salva o valor na posicao certa do vetor C

  end1:
    li a0, 1
    ret


.text
_start:
  ############  Implemente o Parser aqui  #############
  # ------------------------ Zera a Lista C -------------------------- #
  la t0, C                # Carrega a posicao da lista
  li t3, 15               # Numero de iteracoes (elementos da lista - 1)

  loop4:
    sw x0, 0(t0)          # Salva zero na posicao
    addi t0, t0, 4        # Soma 4 ao marcador da posicao (pula para o proximo int)
    addi t3, t3, -1       # Subtrai 1 do contador
    bne x0, t3, loop4     # Enquanto o contador nao for zero, segue o loop

  # ----------------------- Zera a Matriz M -------------------------- #
  la t0, M                # Posicao inicial da matriz M
  li t1, 4800000          # Numero de elementos nela (19,2Mb)
  loop5:
    sw x0, 0(t0)          # Salva zero na posicao
    addi t0, t0, 4        # Soma 4 ao marcador da posicao (pula para o proximo int)
    addi t1, t1, -1       # Subtrai 1 do contador
    bne x0, t1, loop5     # Enquanto o contador nao for zero, segue o loop

  # ------------------- Tratamento da Entrada ----------------------- #
  # ---------------------- Pega o bpm e o tick ------------------------#
  li t3, 0
  jal sp, receive_number
  li t3, 0
  la t0, bpm
  sw a0, 0(t0)

  jal sp, receive_number
  li t3, 0
  la t0, ticks
  sw a0, 0(t0)


  # --------------------------- Trata cada linha ----------------------------- #
  loop6:
    jal ra, get_program
    bne x0, a0, loop6

############        Fim do Parser       #############

play:
  jal time_now
  mv s1, a0 # s1 recebe o tempo atual em ms
  la s2, M
  la s3, C
  la s4, P
  la s5, P2
  li s6, 0xffff
while_1:
  jal time_now        # a0 recebe o tempo atual em ms
  sub s7, a0, s1      # s7 recebe o tempo desde o início da função
  slli a1, s7, 6      # a1 = a1*64 // calculo do deslocamento para linha
  add s8, s2, a1      #s8 = &M + a1 // endereço da linha a ser processada
  jal play_all_channels
j while_1

.data
.align 4
buffer_timeval: .skip 12
buffer_timerzone: .skip 12
P:  .skip 64
P2: .skip 64
C:  .skip 64
.comm	M,19200000,4 # Reserva um espaço de memória com 19.2MB iniciado no endereço marcalo pelo rótulo M

# Buffer para a leitura char a char
char:
  .skip 1

# bpm do arquivo
bpm:
  .skip 4

# ticks do arquivo
ticks:
  .skip 4

#Dados da linha separados de 4 em 4 bytes
linha:
  .skip 24
