#João Gabriel Segato Kruse RA: 218615
lista = input().split()  #Recebe a lista como string e quebra ela em lista
ordem = 0 #Lista inicia desordenada
for i in range(len(lista)):
    lista[i] = int(lista[i])    #Transforma cada item da lista em int
def cresc(lista):   #Quando chamada ordena a lista em ordem crescente
    lista.sort()
    ordem = 1
    return lista, ordem
def decresc(lista): #Quando chamada ordena a lista em ordem decrescente
    lista.sort()
    lista = lista[::-1]
    ordem = -1
    return lista, ordem
def deletar(lista, ra):     #Deleta um ra da lista se ele estiver nela
    if lista == []:
        print("Nao ha alunos cadastrados na turma!")
        return lista
    for i in lista:
        if i == ra:
            lista.remove(ra)
            return lista
    print("Aluno nao matriculado na turma!")
    return lista
def inserir(lista, ra, ordem): #Insere um ra na lista e a posição depende do estado de ordenação da lista
    if len(lista) >= 150:   #Se a lista estiver cheia, não adiciona
        print("Limite de vagas excedido!")
        return lista
    if ra in lista: #Se o ra já estiver na lista, não adiciona novamente
        print("Aluno ja matriculado na turma!")
        return lista
    lista.append(ra)
    if ordem == 1:  #Insere o ra e ordena de forma crescente quando ordem = 1
        lista, ordem = cresc(lista)
    elif ordem == -1:   #Insere o ra e ordena de forma decrescente quando ra = -1
        lista, ordem = decresc(lista)
    return lista
def binary(lista, ra, ordem):#Faz a busca por um ra na lista se esta estiver ordenada
    if ordem == 0:
        print("Vetor nao ordenado!")
    if ordem == 1:
        v = []
        i, f = 0, (len(lista) - 1)
        while(i<=f):
            meio = int((i + f)/2)
            v.append(meio)
            if lista[meio] == ra:
                for i in v:
                    print(i, end=" ")
                print("\n%d esta na posicao: %d"%(ra, meio))
                return None
            elif lista[meio] < ra:
                i = meio + 1
            else:
                f = meio - 1
        for i in v:
            print(i, end=" ")
        print("\n%d nao esta na lista!"%(ra))
    elif ordem == -1:
        v = []
        i, f = 0, (len(lista) - 1)
        while i<=f:
            meio = int((i + f)/2)
            v.append(meio)
            if lista[meio] == ra:
                for i in v:
                    print(i, end=" ")
                print("\n%d esta na posicao: %d"%(ra, meio))
                return None
            elif lista[meio] < ra:
                f = meio - 1
            elif lista[meio] > ra:
                i = meio + 1
        for i in v:
            print(i, end=" ")
        print("\n%d nao esta na lista!"%(ra))
        return None
command = input().split()#Recebe o comando
while command[0] != "s":    #Enquando o comando não for sair, realiza as ações pedidas
    if command[0] == "r":
        lista = deletar(lista, int(command[1]))
    if command[0] == "d":
        lista, ordem = decresc(lista)
    if command[0] == "i":
        lista = inserir(lista, int(command[1]), ordem)
    if command[0] == "p":
        if lista != []:
            for i in lista:
                print(i, end=" ")
            print("\n", end = "")
    if command[0] == "b":
        y = binary(lista, int(command[1]), ordem)
    if command[0] == "c":
        lista, ordem = cresc(lista)
    command = input().split()   #Recebe um novo comando
