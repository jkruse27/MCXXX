        for j in col:
            for k in pont:
                if frase[j].lower() == alt[j] + k:
                    frase[j] = inversas[j] + k
                elif frase[j].lower() == alt[j]:
                    frase[j] = inversas[j]
    for i in frase:
        c = c + i + " "
    frase = c.strip()
    c = ""
    return frase
def substituir(a, b, c, pont, g):
    frase = a.split()
    alt = a.lower()
    for i in pont:
        alt = "".join(alt.split(i))
    alt = alt.split()
    for i in range(0,len(alt)):
        for k in pont:
            if frase[i].lower() == b.lower() + k:
                frase[i] = c + k
            elif frase[i].lower() == b.lower():
                frase[i] = c
    for i in frase:
        g = g + i + " "
    frase = g.strip()
    g = ""
    return frase
while com != "Q":
    action = input()
    if action == "Q":
        com = "Q"
        break
    elif action == "D":
        delete = input()
        frase = apagar(frase, delete, c)
        print(frase)
    elif action == "I":
        inversa = input()
        frase = inverter(frase, inversa, inv, pont, col, c, inversas)
        print(frase)
                                                                                                                                     77,1          88%

