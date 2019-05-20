#João Gabriel Segato Kruse RA:218615
num = int(input())
i, med = 0, 0
iden, pot, c = [], [], []
while i < num:
    valor = input()
    j = valor.split()
    n = int(j[0])
    Pca = int(j[1])
    Pcf = int(j[2])
    M = Pcf/Pca
    iden.append(n)
    pot.append(M)
    i += 1
while True:
    entrada = input()
    if entrada == "0 0":
        break
    e = entrada.split()
    especie = int(e[0])
    CP = int(e[1])
    for r in iden:
        if int(iden[r]) == especie:
            c.append(r)
    for s in c:
        med = med + pot[int(c[s])]
        media = med/len(c)
    estimativa = media *CP
    print(estimativa)

