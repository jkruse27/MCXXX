#João Gabriel Segato Kruse RA:218615
#Objetivo: Implementar um resolvedor de sudoku que envolva recursividade e utilize backtracking


#!/usr/bin/env python3

# Funcao: print_sudoku
# Essa funcao ja esta implementada no arquivo lab20_main.py
# A funcao imprime o tabuleiro atual do sudoku de forma animada, isto e,
# imprime o tabuleiro e espera 0.1s antes de fazer outra modificacao.
# Voce deve chamar essa funcao a cada modificacao na matriz resposta, assim
# voce tera uma animacao similar a apresentada no enunciado.
# Essa funcao nao tem efeito na execucao no Susy, logo nao ha necessidade de
# remover as chamadas para submissao.
from lab20_main import print_sudoku


#Função que checa se o tabuleiro é válido em determinado momento, analisando apenas os pontos de influência
def isValid(mat, linha, coluna):

    #Checa se a linha é valida
    w = []
    for i in mat[linha]:
        if i == 0:
            pass
        elif i not in w:
            w.append(i)
        else:
            return False

    #Checa se a coluna é válida
    y = []
    for i in range(9):
        if mat[i][coluna] == 0:
            pass
        elif mat[i][coluna] not in y:
            y.append(mat[i][coluna])
        else:
            return False

    #Checa se o bloco em que se encontra é válido
    if (coluna % 3) == 0:           #Encontra o quadrante em que está o valor
        col = 0
    elif (coluna % 3) == 1:
        col = 3
    else:
        col = 6

    if (linha % 3) == 0:
        lin = 0
    elif (linha % 3) == 0:
        lin = 3
    else:
        lin = 6

    z = []
    for i in range(lin, lin + 3):
        for j in range(col, col + 3):
            if mat[i][j] == 0:
                pass
            elif mat[i][j] not in z:
                z.append(mat[i][j])
            else:
                return False

    #Retorna True caso não haja nenhum caso inválido
    return True


#Função que através de recursividade e backtracking testa todas as possibilidades e returna true caso exista uma solução e false caso contrário
def solve(mat, lin, col):
    if (lin == 9) and (col == 9) and isValid(mat, lin, col):
        return True
    if mat[lin][col] != 0:  #Caso o número já esteja definido, simplesmente pular para o próximo
        if col < 8:
            solve(mat, lin, col+1)
        else:
            solve(mat, lin+1, 0)
    else:
        for i in range(1, 10):      #Tenta cada número de 1 a 9
            mat[lin][col] = i
            if isValid(mat, lin, col):  #Se o número for possível, segue a chamada recursiva
                if col < 8:
                    solve(mat, lin, col+1)
                else:
                    solve(mat, lin+1, 0)
                if isComplete(mat):
                    return True
        mat[lin][col] = 0
    if (isComplete(mat) != True):          #Caso nenhum número seja válido para a primeira escolha, o jogo é impossível
        return False
    return True
# Funcao: resolve
# Resolve o Sudoku da matriz resposta.
# Retorna True se encontrar uma resposta, False caso contrario
def resolve(resposta):
    res = solve(resposta, 0, 0)
    print_sudoku(resposta)
    return res
