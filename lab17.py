#Nome: João Gabriel Segato Kruse RA:218615
#Objetivo: Criar funções de classe para um programa de gerenciamento de ddos da DAC
class EmailInvalido(Exception):
    pass

class SenhaFraca(Exception):
    pass

class RAInvalido(Exception):
    pass

class Repositorio:
    def __init__(self):
        self.alunos = []
    #Este método recebe o parâmetro aluno e o insere no repositório
    def adicionar(self, aluno):
        import re
        for i in self.alunos:        #Caso o aluno já exista, causa um erro de RA
            if i.ra == aluno.ra:
                raise RAInvalido()
        if re.search(r".?[a-z].?[a-z].?", aluno.senha) and re.search(r".?[A-Z].?", aluno.senha) and len(aluno.senha) >= 8:
            if re.search(r".?[0-9].?[0-9].?", aluno.senha) and re.search(r".?[\!\@\#\$\&\*].?", aluno.senha):
                if re.search(r"[a-zA-Z0-9]+@\w+\.[a-zA-Z][a-zA-Z][a-zA-Z]?[a-zA-Z]?", aluno.email): #Caso a senha esteja dentro das especificações,
                    self.alunos.append(aluno)   #Se o emial estiver correto, adiciona o aluno
                else:
                    raise EmailInvalido()   #Caso contrário, causa um erro de email
            else:
                raise SenhaFraca()
        else:
            raise SenhaFraca()  #Caso a senha não esteja de acordo, causa um erro de senha
    #Este método recebe o parâmetro aluno e altera, no repositório, os dados do aluno com RA igual a aluno.ra
    def alterar(self, aluno):
        import re
        for i in self.alunos:
            if i.ra == aluno.ra:
                if re.search(r".?[a-z].?[a-z].?", aluno.senha) and re.search(r".?[A-Z].?", aluno.senha) and len(aluno.senha) >= 8:
                    if re.search(r".?[0-9].?[0-9].?", aluno.senha) and re.search(r".?[\!\@\#\$\&\*].?", aluno.senha):#Caso a senha esteja dentro das especificações,
                        if re.search(r"[a-zA-Z0-9]+@\w+\.[a-zA-Z][a-zA-Z][a-zA-Z]?[a-zA-Z]?", aluno.email): #Se o emial estiver correto, altera o aluno
                            for i in range(len(self.alunos)):
                                if aluno.ra == self.alunos[i].ra:
                                    self.alunos[i] = aluno
                                    return None
                        else:
                            raise EmailInvalido() #Caso contrário, causa um erro de email
                    else:
                        raise SenhaFraca()
                else:
                    raise SenhaFraca()  #Caso a senha não esteja de acordo, causa um erro de senha
        raise RAInvalido()         #Caso o aluno não exista, causa um erro de RA

    #Este método recebe o parâmetro ra e deve retornar o aluno que possui o RA informado como parâmetro
    def achaAluno(self, ra):
        for i in self.alunos:   #Busca por cada aluno da lista pelo ra
            if i.ra == ra:  #sefor igual, retorna o aluno
                return i
        raise RAInvalido()  #Se o aluno não existir, causa erro de ra
    #Este método recebe o parâmetro ra e deve remover o aluno correspondente do repositório
    def remover(self, ra):
        for i in range(len(self.alunos)):   #Busca por cada aluno na lista
            if self.alunos[i].ra == ra: #Se for igual, deleta o aluno
                del self.alunos[i]
                return None
        raise RAInvalido()  #Se o aluno não estiver na lista, causa erro de ra
    #Este método exclui todos os alunos do repositório.
    def limparRepositorio(self):
        self.alunos = []    #Transforma a lista contendo os alunos em uma lista vazia
