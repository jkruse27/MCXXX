#Nome:João Gabriel Segato Kruse RA:218615
#Objetivo: Criar funções para um sistema de pesquisas
#  Funcao: removePalavras
#
#  Parametros:
#    s: string contendo o texto de entrada
#    vs: lista de strings com as palavras a serem removidas
#
#  Descricao:
#    Deve-se remover as palavras de s que estiverem listadas em vs.
#    Ao final, s nao deve conter espacos extras.
#
# Retorno:
#   string s sem as palavras de vs.

def removePalavras(s, vs):	#Para cada palavra de s, testa se ela é igual a alguma palavra de vs
	s = s.split()
	for i in range(len(vs)):
		if vs[i] in s:
			while (vs[i] in s):	#Se for igua,deleta todas as ocorrêncis dela
				s.remove(vs[i])
	return " ".join(s)     #Retorna a string s sem as palavras de ligação

#  Funcao: pagsResposta
#
# Parametros:
#   paginas: lista de strings cada uma representando uma pagina
#   termosBusca: lista de strings com os termos a serem buscados
#
# Descricao:
#	Deve verificar se cada página em paginas contém todos os termos
#	de busca em termosBusca. Se a paginas[i] contiver todos os termos
#	então deve-se atribuir 1 para resp[i] e 0 caso não contenha pelo
#	menus um dos termos de busca.
#
# Retorno:
#   lista a ser preenchida como resposta, de dimensao numPag.

def pagsResposta(palavrasPagina, termosBusca):
	v = []
	for i in palavrasPagina:		#Pra cada frase em palavrasPagina, transforma ela em lista e testa para ver se tem todas as palavras pedidas
		j = i.split()
		marcador = 0
		for k in termosBusca:
			for l in j:
				if k == l:
					marcador += 1
					break
		if marcador == len(termosBusca):	#Se tiver da append 1 no vetor
			v.append(1)
		else:		#Se não tiver da append 0
			v.append(0)
	return v


#  Funcao: linksResposta
#
# Parametros:
#   links: matriz quadrada binária representando links entre as paginas
#   resp: lista obtido apos execucao de pagsResposta
#
# Descricao:
#   Deve-se preencher uma lista numLinks da seguinte maneira: para cada
#   posicao i (0 <= i < numPags), se resp[i] == 1, então numLinks[i] deve conter
#   o numero de links de outras paginas resposta para i. Caso resp[i] == 0,
#   entao numLinks[i] deve ser -1.
#
# Retorno
#   lista numLinks a ser preenchida como resposta, de tamanho numPag

def linksResposta(links,resp):
	numLinks = []
	for i in range(len(resp)):	#para cada pagina na resp
		marcador = 0
		if resp[i] == 1:		#Se a pagina for relevante analisamos os seus links
			for j in range(len(links)):
					if resp[j] != 0:	#Se a pagina com o link for relevante
						if links[j][i] == 1:	#Se houver o link
							marcador += 1	#Adicionar 1 ao marcador de links
			numLinks.append(marcador)	#adicionar o marcador a numLinks
		elif resp[i] == 0:	#Caso a pagina não seja relevante, adicionamos -1 à numLinks
			numLinks.append(-1)

	return numLinks
