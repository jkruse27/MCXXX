#João Gabriel Segato Kruse RA: 218615
lista = input()
lista = lista.split()
lista = [int(x) for x in lista]
estado = 0                          #Estado da função(1-ordenada crescente, 0-desordenada, -1-ordenada decrescente)
def imprimir(lista):              #Função para imprimir a lista com espaço separando
    if lista != None:
        for i in lista:
            print(i, end = " ")
def ordCresc(lista):                #Função que ordena a lista em ordem crescente
    lista = lista.sort()
    estado = 1
    return lista, estado
def ordDecr(lista):                 #Ordena a lista em ordem decrescente
    a = lista.sort()
    lista = a[::-1]
    estado = -1
    return lista, estado
def inserir(lista, estado, ra):     #Insere o ra na posição dependendo do tipo de ordenação da lista
    for i in lista:
        if i == ra:
            print("Aluno ja matriculado na turma!")
            return lista
    if len(lista) <= 150:       #Se a lista não tiver excedido o seu limite
        if estado == 1:
            for i in range(len(lista)):
                if lista[i] > ra:
                    lista.insert((i-1), ra)
                    return lista
        elif estado == -1:
            for i in range(len(lista)):
                if lista[i] < ra:
                    lista.insert((i-1), ra)
                    return lista
        else:
            lista.append(ra)
        return lista
    print("Limite de vagas excedido!")  #Caso a lista tenha excedido o seu limite
def buscaBin(lista, ra, estado):    #Função para busca binária
    vetor = []
    if estado == 1:                 #Se a lista estiver ordenada:
        inic, final = 0, len(lista) #Define o inicio e o fim da lista
        while(inic <= final):
            meio = (inic + final)/2   #Calcula o meio da lista
            if lista[meio] == ra:       #Se o valor no meio é igual ao buscado, retorna esse valor e a lista de passos até chegar nele
                vetor.append(meio)
                return meio, vetor
            elif lista[meio] < ra:      #Se o valor no meio é menor que o ra buscado, redefine o meio
                vetor.append(meio)
                final = meio -1
                meio = (inic + final)/2
            elif lista[meio] < ra:      #Se o valor no meio é maior que o ra buscado, redefine o meio
                vetor.append(meio)
                inic = meio + 1
                meio = (inic + final)/2
        print("%d nao esta na lista!"%(ra))
    else:
        print("Vetor nao ordenado!")    #Caso a lista não esteja ordenada, imprime isso
def deletar(lista, ra): #Função deletar
    if lista == []:     #Caso a lista esteja vazia, imprime isso
        print("Nao ha alunos cadastrados na turma!")
        return lista
    for i in lista: #Testa para cada valor na lista se é igual ao ra buscado
        if i == ra: #Se for, deleta o ra
            lista.remove(i)
            return lista
    print("Aluno nao matriculado na turma!")    #Se não for, imprime isso
comando = input() #Recebe o primeiro comando
comando = comando.split()
while comando[0] != "s":   #Enquanto o comando não for sair, realiza o loop
    if comando[0] == "r":
        lista = deletar(lista, int(comando[1]))  #Se for remover
    elif comando[0] == "p":
        imprimir(lista) #Se for imprimir
    elif comando[0] == "c":
        lista, estado = ordCresc(lista) #Se for ordenar em ordem crescente
    elif comando[0] == "d":
        lista, estado = ordDecr(lista)  #Se for ordenar em ordem decrescente
    elif comando[0] == "b": #Se for para realizar a busaca binária
        lista, v = buscaBin(lista, int(comando[1]), estado)
        imprimir(v)
        imprimir(lista)
    elif comando[0] == "i": #Se for para inserir um ra
        inserir(lista, estado, int(comando[1]))
    comando = input().split()   #Recebe o comando seguinte
                                                                                                                                     101,1         Fim
                                                                                                                                     66,1          76%
                                                                                                                                     2,1          Topo

