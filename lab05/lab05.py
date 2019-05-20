#João Gabriel Segato Kruse RA: 218615
pvken = 50
pvryu = 50
vryu = 0
vken = 0 
damage = 0
dano = 0
dano = int(input())
dam = 0
dam1 = 0
while (vken + vryu) < 2:
	if dano > 0:
		while dano > 0 and dam1 < pvken:
			damage = dano + damage
			dano = int(input())
			dam1 = dano + damage
	elif dano < 0:
		while dano < 0 and dam < pvryu:		
			damage = dano + damage
			dano = int(input())
			dam = -1*(dano + damage)
	if (vken + vryu) < 3:
		if pvken > 0 and pvryu > 0:
			if damage > 0:
				pv = pvken
				pvken = pvken - damage
				print("Ken: ", pv, " - ", damage, " = ", pvken)
			if damage < 0:
				pv = pvryu
				pvryu = pvryu + damage
				print("Ryu: ", pv, " - ", -1*damage, " = ", pvryu)
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
if vken == 2:
	print("Ken venceu")
elif vken == vryu:
	print("empatou")
elif vryu == 2:
	print("Ryu venceu")
