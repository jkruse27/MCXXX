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

#       Função que testa se o número que será colocado (num) é válido (não está já presente na linha,
#       coluna ou quadrante)
def isValid(mat, linha, coluna, num):
    #Testa se a linha é válida
    if num in mat[linha]:
        return False

    #Testa se a coluna é válida
    for i in mat:
        if num == i[coluna]:
            return False

    #Testa se o bloco é válido
    if (coluna // 3) == 0:           #Encontra o quadrante em que está o valor
        col = 0
    elif (coluna // 3) == 1:
        col = 3
    else:
        col = 6

    if (linha // 3) == 0:
        lin = 0
    elif (linha // 3) == 1:
        lin = 3
    else:
        lin = 6
    for i in range(lin, lin + 3):
        for j in range(col, col + 3):
            if mat[i][j] == num:
                return False

    #Retorna True caso nada seja inválido
    return True


#Função que testa todas as possibilidades de cada posição da matriz
#Altera a matriz e retorna True caso haja solução e False caso contrário
def testa(mat, lin, col):
    if (lin == 9):      #Retorna True caso tenha chegado ao fim sem erros (se chegar na linha 9 quer dizer que está completo)
        return True
    if mat[lin][col] != 0:  #Caso o número já esteja definido, simplesmente pular para o próximo e no backtracking retorna o mesmo que a função que ele chamou
        if col == 8:
            resul = testa(mat, lin + 1, 0)
            if resul:
                return True
            else:
                return False
        else:
            resul = testa(mat, lin, col + 1)
            if resul:
                return True
            else:
                return False
    else:                   #Caso contrário, tenta todas as possibilidades do 1 ao 9, e usando recursividade vai para a próxima posição
        for i in range(1,10):
            if isValid(mat, lin, col, i):
                mat[lin][col] = i
                if (col == 8):
                    resposta = testa(mat, lin + 1, 0)
                    if resposta:
                        return True
                else:
                    resposta = testa(mat, lin, col + 1)
                    if resposta:
                        return True
        mat[lin][col] = 0   #Caso nenhum número de 1-9 seja possível, zera a posição e realiza o backtracking
        return False


# Funcao: resolve
# Resolve o Sudoku da matriz resposta.
# Retorna True se encontrar uma resposta, False caso contrario
def resolve(resposta):
    res = testa(resposta, 0, 0) #Chama a função que resolverá com recursividade e backtracking
    print_sudoku(resposta)
    return res  #Retorna True caso haja solução e False caso contrário
