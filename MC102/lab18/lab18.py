#João Gabriel Segato Kruse ra:218615
#Objetivo: Receber uma imagem e realizar convoluções nela
import sys
#Função que recebe o  arquivo, abre-o e devolve a matriz presente nele e uma matriz vazia igual a original
def matrix(arq):
    img = open(arq, "r")                   #Abre o arquivo
    y = img.readline()                      #Lê a primeira linha para avançar o marcador de posição
    s, mat= img.readline(), []    #Cria dois vetores e lê a linha com as dimensôes da matriz
    nov = []
    x = img.readline()                      #Lê a linha para avançar o marcador
    r = s.split()                           #Cria lista com as dimensões da matriz
    for i in range(int(r[1])):
        a = img.readline().split()          #Lê cada linha de valores da matriz imagem e transforma em 2 matrizes, uma para ser modificada
        v, p = [], []
        for j in range(int(r[0])):
            v.append(int(a[j]))
            p.append(int(a[j]))
        mat.append(v)                       #matriz base
        nov.append(p)                       #matriz que será modificada
    img.close()                             #Fecha o arquivo
    return mat, nov                         #Retorna 2 matrizes iguais, uma para ser modificada e outra base

#Função que recebe um arquivo, abre-o e devove o divisor e a matriz presentes nele
def conv(arq):
    conv = open(fileMatriz, "r")    #Abre o arquivo
    d = int(conv.readline())        #Lê a linha com o valor do divisor e slava em d
    c = []
    for i in range(3):              #Lê as linhas com os valores da matriz de convoluçãoe transforma em uma matriz
        b = conv.readline().split()
        g = []
        for j in range(3):
            g.append(int(b[j]))
        c.append(g)                 #Adiciona cada linha à matriz de convolução c
    conv.close()                    #Fecha o arquivo
    return d, c                     #Retorna o divisor e a matriz de convolução

#Função que retorna o novo valor na posição da matriz
def soma(mat, conv, div, linha, coluna):
    soma = 0                        #Realiza a soma de todos as multiplicações por posição da matriz
    for i in range(3):
        for j in range(3):
            soma += (conv[i][j]*mat[linha+i-1][coluna+j-1])
    if (int(soma/div) >= 0) and (int(soma/div) <= 255):
        return int(soma/div)                 #Retorna a parte inteira da soma dividida pelo divisor
    elif (int(soma/div) < 0):
        return 0
    else:
        return 255
#Recebe os nomes dos arquivos com a imagem original e a matriz de convolução e o divisor
fileImage = sys.argv[1]
fileMatriz = sys.argv[2]

#Abre os arquivos e salva o conteudo de cada um deles conteudo em uma matriz ou variável adequada
matriz, nova = matrix(fileImage)
divisor, convolucao = conv(fileMatriz)
#Completa a nova matriz com os valores corretos
for i in range(1, len(matriz)-1):
    for j in range(1, len(matriz[i])-1):
        nova[i][j] = soma(matriz, convolucao, divisor, i, j)

#Dá um print no arquivo no formato da imagem
print("P2")
print("%d %d" %(len(matriz[0]), len(matriz)))
print(255)
for i in range(len(matriz)):
    for j in range(len(matriz[i])):
        print(int(nova[i][j]), end=" ")
    print()
