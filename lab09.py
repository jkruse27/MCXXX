#João Gabriel Segato Kruse RA:218615
#lab09 encontrar a forma com a qual se obtem mais lucro
periodo, d, lucro, vez, deletadas, empDia = float(input()), 0, 0, 0, [], []
emp1, emp2, emp3, emp4, comprada = [0]*int(periodo),[0]*int(periodo),[0]*int(periodo),[0]*int(periodo), [0]*(int(periodo)-1)
completa, lucroDia, compra, possibilidades, lucros = [emp1, emp2, emp3, emp4], [], [], [], []
for i in range(len(completa)):
	for j in range(int(periodo)):
		completa[i][j] = float(input())
for i in range(int(periodo)-1):	
	lucroDia.append([])
for i in range(0, 5**(int(periodo)-1)):
	possibilidades.append([])
	lucros.append([])
	empDia.append([])
while d < periodo:
	for i in range(len(completa)):
		if d+1 == periodo:			
			break
		else:
			lucroDia[d].append(float(completa[i][d+1] - completa[i][d]))
for i in range(len(lucroDia)):
	lucroDia.append(0)
	d += 1
while vez < len(possibilidades)-1:
	for i in range(len(lucroDia)):
		possibilidades[vez].append(lucroDia[i][vez%5])	
		empDia[vez].append(vez%5)
	vez += 1
print(len(possibilidades))
for i in range(len(possibilidades)):
	for j in possibilidades[i]:
		if j < 0:
			deletadas.append(i)
for i in sorted(deletadas, reverse = True):
	del empDia[i]
	del possibilidades[i]
deletadas = []
for i in range(len(possibilidades)):
	for j in possibilidades[i]:
		lucro = lucro + j
	if lucro >= 0:
		lucros[i].append(lucro)
	else:
		deletadas.append(i)
	lucro = 0
for i in sorted(deletadas, reverse = True):
	del empDia[i]
	del possibilidades[i]
matriz = [[], [], [], []]
deletadas = []
for i in range(len(empDia)):
	for j in enumerate(empDia):
		if empDia[j] == 0:
			matriz[0].append(j)
		if empDia[j] == 1:
			matriz[1].append(j)
		if empDia[j] == 2:
			matriz[2].append(j)
		if empDia[j] == 3:
			matriz[3],append(j)
	for i in range(len(matriz)):
		for j in range(len(matriz[i])-1):
			if matriz[i][j] != matriz[i][j+1]:
				deletadas.append(i)
	for i in sorted(deletadas, reverse = True):
		del empDia[i]
		del possibilidades[i]
		del lucros[i]
comprei = max(lucros)
for i in lucros:
	if i == comprei:
		datinha = empDia[i]
		verdade = possibilidades[i]
print(datinha, comprei, verdade)

#	print("acao %d: compra %d, venda %d, lucro %.2f" % (empresa, dia_compra, dia_venda, lucro))
#	print("Lucro: %.2f" % (lucro))
		




