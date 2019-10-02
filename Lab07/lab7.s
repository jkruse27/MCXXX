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

# Ignora toda a linha do head
ignore_head:
  loop:
    li a0, 0          # stdin
    la a1, char         # discards
    li a2, 1          # size 1
    li a7, 63         # syscall read
    ecall

    la t0, char
    lb t0, 0(t0)

    addi t0, t0, -10  # verifica se a letra e '\n' ('\n' = 10), se n - 10 = 0, n = '\n'
    bne t0, x0, loop  # se a letra for \n, sai do loop

  jalr x0, t1, 0

# Ignora a palavra Program
ignore_program:
  loop1:
    li a0, 0          # stdin
    la a1, char         # discards
    li a2, 1          # size 1
    li a7, 63         # syscall read
    ecall

    la t0, char
    lb t0, 0(t0)

    addi t0, t0, -32  # verifica se a letra e ' ' (' ' = 32), se n - 32 = 0, n = ' '
    bne t0, x0, loop1  # se a letra for ' ', sai do loop

  jalr x0, t1, 0

# Trata cada linha dependendo do caso
get_program:
  li a0, 0          # stdin
  la a1, char       # discards
  li a2, 1          # size 1
  li a7, 63         # syscall read
  ecall

  la t0, char
  lb t0, 0(t0)

  li t1, 72         # Se a letra for "h" indica que e um head
  beq t0, t1, h
  li t1, 80         # Se a letra for "p" indica que e um program
  beq t0, t1, p
  #Tratar linha de tempos/nota/etc
  j end1
  h:
    jal t1, ignore_head
    j end1
  p:
    jal t1, ignore_program
    loop3:
      li a0, 0          # stdin
      la a1, char         # discards
      li a2, 1          # size 1
      li a7, 63         # syscall read
      ecall

      la t0, char
      lb t0, 0(t0)

      addi t1, t0, -10        # verifica se a letra e '\n' ('\n' = 10), se n - 10 = 0, n = '\n'
      bne t1, x0, line_end

      addi t1, t1, -22        # verifica se a letra e ' ' (' ' = 32), se n - 32 = 0, n = ' '
      bne t1, x0, new_word

      li t2, 10
      mul a3, a3, t2
      addi a3, t0, -48
      j loop3

      new_word:
        mv s0, a3
        j loop3               # se a letra for ' ', sai do loop

      line_end:               # Quando chega no final da linha, adiciona o intrumento na faixa da lista C
        la t0, C              # Endereco de C
        li t5, 4
        addi s0, s0, -1
        mul s0, s0, t5        # Adiciona a 4*(faixa - 1) e depois soma com a posicao inicial para achar a posicao do vetor
        add t0, t0, s0
        sw a3, 0(t0)          # Salva o valor na posicao certa do vetor C

  end1:
    ret


.text
_start:
############  Implemente o Parser aqui  #############

  # ------------------- Zera a Lista C ------------------------ #
  la t0, C                # Carrega a posicao da lista
  li t3, 15               # Numero de iteracoes (elementos da lista - 1)

  loop4:
    sw x0, 0(t0)          # Salva zero na posicao
    addi t0, t0, 4        # Soma 4 ao marcador da posicao (pula para o proximo int)
    addi t3, t3, -1       # Subtrai 1 do contador
    bne x0, t3, loop4     # Enquanto o contador nao for zero, segue o loop

  # ------------------- Zera a Matriz M ------------------------ #
  la t0, M                # Posicao inicial da matriz M
  li t1, 4800000          # Numero de elementos nela (19,2Mb)
  loop5:
    sw x0, 0(t0)          # Salva zero na posicao
    addi t0, t0, 4        # Soma 4 ao marcador da posicao (pula para o proximo int)
    addi t1, t1, -1       # Subtrai 1 do contador
    bne x0, t1, loop5     # Enquanto o contador nao for zero, segue o loop

  # ------------------- Tratamento da Entrada ----------------------- #

  loop6:
    jal ra, get_program
    beq x0, a0, end2
    j loop6

  end2:

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
char:
  .skip 1
