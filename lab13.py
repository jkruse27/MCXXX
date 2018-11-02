#João Gabriel Segato Kruse RA:218615
#o objetivo desse lab é simular uma tabela de campeonato levando em conta as diversas possibilidades
#!/usr/bin/env python3
#*******************************************************************************
# Funcao: atualizaTabela
#
# Parametros:
#   tabela: uma matriz com os dados da tabela do campeonato
#   jogo: string contendo as informações de um jogo no formato especificado no lab.
#
# Descrição:
#   Deve inserir as informações do parametro 'jogo' na tabela.
#   OBSERVAÇÃO: nesse momento não é necessário ordenar a tabela, apenas inserir as informações.
def atualizaTabela(tabela, jogo):
#  -- INSIRA SEU CÓDIGO AQUI -- #
#*******************************************************************************
    jog = jogo.split()  #Separa a string da partida
    time1 = [jog[0], int(jog[1])]   #Salva em uma lista o nome e o número de gols do time1([nome, gols])
    time2 = [jog[4], int(jog[3])]   #Salva em uma lista o nome e o número de gols do time2([nome, gols])
    if time1[1] > time2[1]: #Se o número de gols do time1 for maior
        for i in range(len(tabela)):    #Atualiza a as vitorias e pontos do time1(como o time 2 perdeu, não muda)
            if time1[0] == tabela[i][0]:
                tabela[i][1] = tabela[i][1] + 3
                tabela[i][2] = tabela[i][2] + 1
    elif time1[1] < time2[1]:   #Se o número de gols do time2 for maior
        for i in range(len(tabela)):    #Atualiza a as vitorias e pontos do time2(como o time1 perdeu, não muda)
            if time2[0] == tabela[i][0]:
                tabela[i][1] = tabela[i][1] + 3
                tabela[i][2] = tabela[i][2] + 1
    elif time1[1] == time2[1]: #Em caso de empate
        for i in range(len(tabela)):    #Atualiza os pontos dos 2 times(o número de vitórias segue igual)
            if time2[0] == tabela[i][0]:
                tabela[i][1] = tabela[i][1] + 1
            elif time1[0] == tabela[i][0]:
                tabela[i][1] = tabela[i][1] + 1
    for i in range(len(tabela)):    #Atualiza o número e o saldo de gols dos dois times
        if time1[0] == tabela[i][0]:
            tabela[i][3] = tabela[i][3] + time1[1] - time2[1]
            tabela[i][4] = tabela[i][4] + time1[1]
        if time2[0] == tabela[i][0]:
            tabela[i][3] = tabela[i][3] + time2[1] - time1[1]
            tabela[i][4] = tabela[i][4] + time2[1]
#*******************************************************************************
# Funcao: comparaTimes
#
# Parametros:
#   time1: informações de um time
#   time2: informações de um time
#
# Descricão:
#   retorna 1, se o time1>time2, retorna -1, se time1<time2, e retorna 0, se time1=time2
#   Observe que time1>time2=true significa que o time1 deve estar em uma posição melhor do que o time2 na tabela.
def comparaTimes(time1, time2):
#  -- INSIRA SEU CÓDIGO AQUI -- #
#*******************************************************************************
    if (time1 > time2) == True:   #Testa qual time venceu
        return 1
        print("oi")
    elif (time1 < time2) == True:
        return -1
        print("tchau")
    else:
        return 0
#*******************************************************************************
# Funcao: ordenaTabela
#
# Parametros:
#   tabela: uma matriz com os dados da tabela do campeonato.
#
# Descricão:
#   Deve ordenar a tabela com campeonato de acordo com as especificaçoes do lab.
#
def ordenaTabela(tabela):
#  -- INSIRA SEU CÓDIGO AQUI -- #
#*******************************************************************************
  #Ordena a tabela seguindo a ordem de importância
    for i in range(len(tabela)-1):
        for j in range(len(tabela) - 1):
            if comparaTimes(tabela[j][1], tabela[j+1][1]) == -1:   #Maior número de pontos
                tabela[j], tabela[j+1] = tabela[j+1], tabela[j]
            elif comparaTimes(tabela[j][1], tabela[j+1][1]) == 0:   #Caso de empate
                if comparaTimes(tabela[j][2], tabela[j+1][2]) == -1:   #Maior número de vitórias
                    tabela[j], tabela[j+1] = tabela[j+1], tabela[j]
                elif comparaTimes(tabela[j][2], tabela[j+1][2]) == 0:    #Caso de empate
                    if comparaTimes(tabela[j][3], tabela[j+1][3]) == -1:   #Saldo de gols
                        tabela[j], tabela[j+1] = tabela[j+1], tabela[j]
                    elif comparaTimes(tabela[j][3], tabela[j+1][3]) == 0:    #Caso de empate
                        if comparaTimes(tabela[j][4], tabela[j+1][4]) == -1:   #Gols pró
                            tabela[j], tabela[j+1] = tabela[j+1], tabela[j]


#*******************************************************************************
# Funcao: imprimeTabela
#
# Parametros:
#   tabela: uma matriz com os dados da tabela do campeonato.
#
# Descrição:
#   Deve imprimir a tabela do campeonato de acordo com as especificações do lab.
def imprimeTabela(tabela):
#  -- INSIRA SEU CÓDIGO AQUI -- #
#*******************************************************************************
    for i in range(len(tabela)):
        for j in range(len(tabela[i])):
            tabela[i][j] = str(tabela[i][j])    #Transforma cada item da matriz em string
    for i in tabela:    #Concatena cada linha da matriz(time da tabela) separando com ", "
        print(", ".join(i)) #Imprime cada time
