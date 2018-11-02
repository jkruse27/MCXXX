#João Gabriel Segato Kruse RA:218615
#Objetivo: Simular um jogo de batalha naval

#Funçãoque encontra todas as posições de um navio e retorna em uma matriz de vetores
def find(mat, pos, v, anterior):
    m = [[pos[0]+1,pos[1]], [pos[0]-1, pos[1]], [pos[0], pos[1]+1], [pos[0], pos[1]-1]]
    for i in m:
        try:
            if (mat[i[0]][i[1]] == "@") and ([i[0], i[1]] not in anterior) and (i[0] >= 0) and (i[1] >= 0):
                anterior.append(pos)
                v = find(mat, i, v, anterior)
        except IndexError:
            pass
    v.append(pos)
    return v

#Função que recebe uma matriz e uma posição e retorna a matriz após a operação além de um marcador de término de jogo
def destroy(mat, pos):
    acabou = True
    if (mat[pos[0]][pos[1]] == "@"):
        delete = find(mat, pos, [], [])
        for i in delete:
            mat[i[0]][i[1]] = "-"
    c = 0
    for i in mat:
        if "@" in i:
            acabou = False
    return mat, acabou

#Recebe um input e encontra os valores para as dimensões da matriz e cria os dois tabuleiros
a, counter = input().split('x'), 1
coluna, linha, finish = a[0], a[1], False
tabuleiro1, tabuleiro2 = [list(input()) for i in range(int(coluna))], [list(input()) for i in range(int(coluna))]

#Enquanto nenhum dos jogadores perdeu, recebr nova jogada e realizar ação, imprimindo a ação e o tabuleiro depois dela ocorrer
while finish == False:
    if ((counter%2) != 0):
        posicao = [int(i) for i in input().split(",")]
        tabuleiro2, finish = destroy(tabuleiro2, [posicao[0]-1, posicao[1]-1])
        print("Ataque em (%d,%d) do jogador 1" %(posicao[0], posicao[1]))
        for i in range(len(tabuleiro2)):
            print("".join(tabuleiro2[i]))
    if ((counter%2) == 0):
        posicao = [int(i) for i in input().split(",")]
        tabuleiro1, finish = destroy(tabuleiro1, [posicao[0]-1, posicao[1]-1])
        print("Ataque em (%d,%d) do jogador 2" %(posicao[0], posicao[1]))
        for i in range(len(tabuleiro1)):
            print("".join(tabuleiro1[i]))
    counter += 1
