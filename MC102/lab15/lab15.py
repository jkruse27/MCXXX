#João Gabriel Segato Kruse RA:218615
#Funções para um programa que realiza operações com conjuntos
#!/usr/bin/env python3

# Funcao: pertence
#
# Parametros:
#   conj: vetor contendo o conjunto de entrada
#    num: elemento a ser verificado pertinencia
#
# Retorno:
#   True se num pertence a conj e False caso contrario
#
def pertence(conj, num):
    for i in conj:          #Para cada elemento do conjunto, testa se algum deles é igual a num
        if i == num:
            return True
    return False    #Se nenhum for, retorna false

# Funcao: contido
#
# Parametros:
#   conj1: vetor contendo um conjunto de entrada
#   conj2: vetor contendo um conjunto de entrada
#
# Retorno:
#   True se conj1 esta contido em conj2 e False caso contrario
#
def contido(conj1, conj2):
    for i in conj1:     #Para cada elemento de conj1, se o elemento não estiver em conj2, retorna false
        if (i in conj2) == False:
            return False
    return True #Se todos elementos de conj1 estão em conj2, retorna True

# Funcoes: adicao e subtracao
#
# Parametros:
#   conj: vetor contendo o conjunto que tera incluso ou removido o elemento
#    num: elemento a ser adicionado ou removido
#
def adicao(conj, num):
    if (num in conj) == False:  #Se o elemento não está no conjunto, adiocionamos ele
        conj.append(num)
    return conj  #retornamos a lista

def subtracao(conj, num):
    if num in conj:  #se o elemento está no conjunto, removemos ele
        conj.remove(num)
    return conj  #retornamos a lista

# Funcoes: uniao, intersecao e diferenca
#
# Parametros:
#     conj1: vetor contendo o conjunto de entrada do primeiro operando
#     conj2: vetor contendo o conjunto de entrada do segundo operando
#
# Retorno:
#   Vetor contendo o conjunto de saida/resultado da operacao
#
def uniao(conj1, conj2):
    conj = []
    for i in conj2: #Para cada elemento de conj2, se ele não está em conj 1, adicioná-lo a conj1
        if (i in conj1) == False:
            conj.append(i)
    for i in conj1:
        conj.append(i)
    return conj  #retornamos a lista

def intersecao(conj1, conj2):
    inter = []  #Para cada elemento de conj1, se ele está em conj2, inserimos ele em uma nova lista
    for i in conj1:
        if (i in conj2):
            inter.append(i)
    return inter    #retornamos a lista

def diferenca(conj1, conj2):
    dif = []
    for i in conj1:
        if (i in conj2) == False:
            dif.append(i)
    return dif

def uniao_disjunta(conj1, conj2):
    return diferenca(conj1, conj2) + diferenca(conj2, conj1)  #retornamos a lista resultado da soma das diferenças das listas
