#João Gabriel Segato Kruse RA: 218615
pvken = 50
pvryu = 50
vryu = 0
vken = 0
damage = 0
dano = int(input())
while (vken + vryu) < 2:
    if dano > 0:
        while dano > 0 and damage < pvken:
            damage = dano + damage
            dano = int(input())
            if vken == 1 or vryu == 1:
                                if pvken - damage - dano <= 0:
                                        vryu = vryu + 1
                                        if vryu == vken:
                                                pvken = pvken - damage - dano
                                                print("Ken:", pv, "-", damage + dano, "=", pvken)
                                                print("empatou")
                                        elif vryu == 2:
                                                pvken = pvken - damage - dano
                                                print("Ken:", pv, "-", damage + dano, "=", pvken)
                                                print("Ryu venceu")
    elif dano < 0:
        while dano < 0 and -1*damage < pvryu:
            damage = dano + damage
            dano = int(input())
            if vken == 1 or vryu == 1:
                                if pvryu + damage + dano <= 0:
                                        vken = vken + 1
                                        if vryu == vken:
                                                pvryu = pvryu + damage + dano
                                                print("Ryu:", pv, "-", (damage + dano)*-1, "=", pvryu)
                                                print("empatou")
                                        elif vken == 2:
                                                pvryu = pvryu + damage + dano
                                                print("Ryu:", pv, "-", (damage + dano)*-1, "=", pvryu)
                                                print("Ken venceu")

    if (vken + vryu) < 3:
        if pvken > 0 and pvryu > 0:
            if damage > 0:
                pv = pvken
                pvken = pvken - damage
                print("Ken:", pv, "-", damage, "=", pvken)
            if damage < 0:
                pv = pvryu
                pvryu = pvryu + damage
                print("Ryu:", pv, "-", -1*damage, "=", pvryu)
        if pvken <= 0:
            vryu = vryu + 1
            pvryu = 50
            pvken = 50
        if pvryu <= 0:
            vken = vken + 1
            pvryu = 50
            pvken = 50
    damage = 0
    continue

                                                                                                                                     60,0-1        Fim

