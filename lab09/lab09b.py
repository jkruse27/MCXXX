#João Gabriel Segato Kruse RA:218615
#lab09, encontrar opção com lucro máximo possível
import itertools
periodo = float(input())
cada, completa, possibilidades, num = [], [], [], [[1, 2, 3, 4, 0]]*(int(periodo)-1)
for i in range(int(periodo)):
    completa.append([])
for j in range(4):
    for i in range(int(periodo)):
        completa[i].append(float(input()))
for i in range(len(completa)):
    completa[i].append(0)
lucros, lucro = [], []
for i in range(len(completa)):
    for j in range(len(completa[i])):
        if i + 1 != len(completa):
            lucro.append(completa[i+1][j]-completa[i][j])
    if i + 1 == len(completa):
        break
    lucros.append(lucro)
    lucro = []
nums = []
delete = []
for combinations in itertools.product(*num):
    nums.append(combinations)
for combinations in itertools.product(*lucros):
    possibilidades.append(combinations)
for i in range(len(possibilidades)):
    for j in possibilidades[i]:
        if j < 0:
            delete.append(i)
            break
for i in sorted(delete, reverse = True):
    del possibilidades[i]
    del nums[i]
lista, l = [], []
occurrences = lambda s, nums: (i for i, e in enumerate(nums) if e == s)
for i in range(1, 5):
    for j in nums:
            l.append(list(occurrences(i, j)))
    lista.append(l)
    l = []
                                                                                                                                     2,1          Topo
delete = []
for i in range(len(lista)):
    for j in range(len(lista[i])):
        for k in range(len(lista[i][j])-1):
            if lista[i][j][k] + 1 != lista[i][j][k+1]:
                delete.append(j)
                break
for i in sorted(delete, reverse = True):
    del possibilidades[i]
    del nums[i]
lucros, lc = [], 0
for i in range(len(possibilidades)):
    for j in range(len(possibilidades[i])):
        lc = lc + possibilidades[i][j]
    lucros.append(lc)
    lc = 0
lucroVer = max(lucros)
diaVer = nums[lucros.index(lucroVer)]
diaCompra = [[], [], [], []]
if (1 in diaVer) == True:
    diaCompra[0].append(diaVer.index(1)+1)
    diaCompra[0].append(len(diaVer)+1-diaVer[::-1].index(1))
    diaCompra[0].append(completa[diaCompra[0][1]-1][0] - completa[diaCompra[0][0]-1][0])
if (2 in diaVer) == True:
    diaCompra[1].append(diaVer.index(2)+1)
    diaCompra[1].append(len(diaVer)+1-diaVer[::-1].index(2))
    diaCompra[1].append(completa[diaCompra[1][1]-1][1] - completa[diaCompra[1][0]-1][1])
if (3 in diaVer) == True:
    diaCompra[2].append(diaVer.index(3)+1)
    diaCompra[2].append(len(diaVer)+1-diaVer[::-1].index(3))
    diaCompra[2].append(completa[diaCompra[2][1]-1][2] - completa[diaCompra[2][0]-1][2])
if (4 in diaVer) == True:
    diaCompra[3].append(diaVer.index(4)+1)
    diaCompra[3].append(len(diaVer)+1-diaVer[::-1].index(4))
    diaCompra[3].append(completa[diaCompra[3][1]-1][3] - completa[diaCompra[3][0]-1][3])
for i in range(len(diaCompra)):
    if (diaCompra[i]) != []:
        print("acao %d: compra %d, venda %d, lucro %.2f" % (i+1, diaCompra[i][0], diaCompra[i][1], diaCompra[i][2]))
print("Lucro: %.2f" % (lucroVer))
                                                                                                                                     81,1          Fim

