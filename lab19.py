#João Gabriel Segato Kruse RA: 218615
#Objetivo: Encontrar utilizando recursividade uma cadeia hierárquica de uma
#empresa a partir de determinado funcionário

#Função recursiva que recebe a matriz de relações e encontra e imprime a cadeia hierárquica
def cadeia(mat, n, poss):
    for i in range(len(mat[n])):
        if mat[n][i] == "1":
            cadeia(mat, i, poss)
            poss.append(i)
    return poss

#Recebe os valores para a matriz de hierarquia e definimos inicio como o funcionário a partir do qual se fará a cadeia hierárquica
entrada, matriz= input().split(), []
total, inicio, poss = int(entrada[0]), int(entrada[1]), []
for i in range(total):
    matriz.append(input().split())

#Chama a função cadeia que encontrará a cadeia hierárquica, recebe e ordena o vetor contendo a hierarquia e depois imprime-o
a = cadeia(matriz, inicio, poss)
a.sort()
a.insert(0, str(inicio))
a = [str(i) for i in a]
print(" ".join(a))
