# Laboratorio 12 - Tetris
# Nome: João Gabriel Segato Kruse
# RA:218615

ALTURA_TABULEIRO = 10
LARGURA_TABULEIRO = 10

# Funcao: atualiza_posicao
#
# Parametros:
#      l: largura do bloco que ira cair
#      a: altura do bloco que ira cair
#      x: posicao horizontal inicial do bloco que ira cair
#   desl: deslocamento horizontal a ser aplicado ao bloco (positivo para direita, negativo para a esquerda)
#    rot: 1 se deve rotacionar o bloco, 0 caso contrario
#
# Retorno:
#   Nova largura, altura e posicao horizontal.
#
def atualiza_posicao(l, a, x, desl, rot):
    if rot == 1:    #Caso haja rotação, inverte larugura e altura
        b = []
        b.append(l)
        b.append(a)
        a = b[0]
        l = b[1]
    if (x + desl) >= 0 and (x + desl + l) < 10: #Realiza o deslocamento em x se o
        x = x + desl                            #bloco não sair do limite
    elif (x + desl) < 0: #Deslocamento caso o bloco sai do limite por 0
        x = 0
    elif (x + desl + l) >= 10: #Deslocamento caso o bloco saia do limite por 10
        x = 10 - l
    return l, a, x

# Funcao: encontra_y
#
# Parametros:
#    mat: matriz representando o tabuleiro
#      l: largura do bloco que ira cair
#      x: posicao horizontal do bloco que ira cair
#
# Retorno:
#   altura final y do canto inferior esquerdo do bloco apos
#   este descer o maximo possivel
#
def encontra_y(mat, l, x):
    y = 0
    for i in range(10):             #Procura em cada linha das colunas dentro do comprimento de x por um 1
        for j in range(x, (x + l)):
            if mat[i][j] == 1 and (i + 1) > y:  #Seleciona a maior altura
                y = i + 1
    return y

# Funcoes: posicao_final_valida
#
# Parametros:
#      a: altura do bloco que caiu
#      y: altura final do bloco que caiu
#
# Retorno:
#   1 se o bloco naquela posicao estiver contido dentro do tabuleiro, ou 0 caso contrario.
#
def posicao_final_valida(a, y):
    if (y + a - 1) < 10:    #Testa se o bloco não excede a altura limite
        return 1
    else:
        return 0

# Funcoes: posiciona_bloco
#
# Parametros:
#    mat: matriz do tabuleiro
#      l: largura do novo bloco
#      a: altura do novo bloco
#      x: posicao horizontal do novo bloco
#      y: altura final do novo bloco
#
#      Deve preencher com 1s as novas posições ocupadas pelo bloco que caiu
# Retorno:
#   NULL
#
def posiciona_bloco(mat, l, a, x, y):
    for i in range(y, y + a):       #Completa a matriz com 1 no local onde o bloco caiu
        for j in range(x, x + l):
            mat[i][j] = 1

# Funcoes: atualiza_matriz
#
#    mat: matriz do tabuleiro
#
#         Deve remover as linhas totalmente preenchidas do tabuleiro copiando
#         linhas posicionadas acima.
# Retorno:
#   retorna o numero de linhas totalmente preenchidas que foram removidas apos
#   a atualizacao do tabuleiro.
#
def atualiza_matriz(mat):
    marcador, v = 0, []
    for i in range(len(mat)):   #Salva em v o número de  cada linha totalmente preenchida
        if mat[i] == [1]*10:
            v.append(i)
    for i in sorted(v, reverse = True): #Deleta as linhas preenchidas
        del mat[i]
    marcador = len(v)   #O número de linhas deletadas é a lenght de v
    for i in range(marcador):       #Coloca uma linha de 0s no topo da matriz para cada linha deletada
        mat.append([0, 0, 0, 0, 0, 0, 0, 0, 0, 0])
    return marcador
