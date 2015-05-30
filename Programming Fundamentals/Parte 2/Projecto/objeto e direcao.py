#==========================================================
#DEFINICAO DE OBJECTO
#==========================================================

#==========================================================
#CONSTRUTORES
#==========================================================

espaco = 'espaco'
comida = 'comida'
premio = 'premio'
monstro = 'monstro'
parede = 'parede'
desconhecido = 'desconhecido'

#==========================================================
#RECONHECEDORES
#==========================================================

#espaco_p: objecto -> logico
#Apresenta o valor True se o objecto dadpo for "espaço",
#apresentando False se o objecto não for válido ou se nao
#for "espaço"
def espaco_p(obj):
    return isinstance (obj,str) and obj == espaco

#comida_p: objecto -> logico
#Apresenta o valor True se o objecto dadpo for "comida",
#apresentando False se o objecto não for válido ou se nao
#for "comida"
def comida_p(obj):
    return isinstance (obj,str) and obj == comida

#premio_p: objecto -> logico
#Apresenta o valor True se o objecto dadpo for "premio",
#apresentando False se o objecto não for válido ou se nao
#for "premio"
def premio_p(obj):
    return isinstance (obj,str) and obj == premio

#monstro_p: objecto -> logico
#Apresenta o valor True se o objecto dadpo for "monstro",
#apresentando False se o objecto não for válido ou se nao
#for "monstro"
def monstro_p(obj):
    return isinstance (obj,str) and obj == monstro

#parede_p: objecto -> logico
#Apresenta o valor True se o objecto dadpo for "parede",
#apresentando False se o objecto não for válido ou se nao
#for "parede"
def parede_p(obj):
    return isinstance (obj,str) and obj == parede

#desconhecido_p: objecto -> logico
#Apresenta o valor True se o objecto dadpo for "desconhecido",
#apresentando False se o objecto não for válido ou se nao
#for "desconhecido"
def desconhecido_p(obj):
    return isinstance (obj,str) and obj == desconhecido

#==========================================================
#TESTES
#==========================================================

#objetos_iguais: objecto1 x objecto2 -> logico
#objectos_iguais recebe dois objectos e devolve o valor
#lógico True se os dois objectos forem iguais, devolvendo
#False caso contrário
def objectos_iguais(obj1, obj2):
    return obj1 == obj2

#==========================================================
#DEFENICAO DE DIRECCAO
#==========================================================

#==========================================================
#CONSTRUTORES
#==========================================================

norte = 'norte'
sul = 'sul'
este = 'este'
oeste = 'oeste'

#==========================================================
#RECONHECEDORES
#==========================================================

#norte_p: direcao -> logico
#Apresenta o valor True se a direcção dada for "norte",
#apresentando False se a direcção nõ for válida ou se nao
#for "norte"
def norte_p (direcao):
    return isinstance (direcao,str) and direcao == norte

#sul_p: direcao -> logico
#Apresenta o valor True se a direcção dada for "sul",
#apresentando False se a direcção nõ for válida ou se nao
#for "sul"
def sul_p (direcao):
    return isinstance (direcao,str) and direcao == sul

#este_p: direcao -> logico
#Apresenta o valor True se a direcção dada for "este",
#apresentando False se a direcção nõ for válida ou se nao
#for "este"
def este_p (direcao):
    return isinstance (direcao,str) and direcao == este

#oeste_p: direcao -> logico
#Apresenta o valor True se a direcção dada for "oeste",
#apresentando False se a direcção nõ for válida ou se nao
#for "oeste"
def oeste_p (direcao):
    return isinstance (direcao,str) and direcao == oeste

#==========================================================
#TESTES
#==========================================================

#direcoes_iguais: direcao1 x direcao2 -> logico
#direcoes_iguais devolve True se as direcoes dadas sao iguais
#devolvendo False caso contrário
def direcoes_iguais (direcao1,direcao2):
    return direcao1 == direcao2

#==========================================================
#OPERACOES
#==========================================================

#vira_esquerda: direcao -> direcao
#vira_esquerda(direccao) recebe uma direcção e devolve a direcção à esquerda
def vira_esquerda (direcao):
    if isinstance (direcao,str):
        if direcao == norte:
            return oeste
        if direcao == oeste:
            return sul
        if direcao == sul:
            return este
        if direcao == este:
            return norte

#vira_direita: direcao -> direcao
#vira_direita(direccao) recebe uma direcção e devolve a direcção à direita
def vira_direita (direcao):
    if isinstance (direcao,str):
        if direcao == norte:
            return este
        if direcao == este:
            return sul
        if direcao == sul:
            return oeste
        if direcao == oeste:
            return norte
        
#==========================================================
#DEFINICAO DE POSICAO
#==========================================================

#==========================================================
#CONSTRUTORES
#==========================================================

#cria_posicao: inteiro, inteiro -> posicao
#cria_posicao(coluna,linha) tem como valor uma possicao com o número de colunas e linhas dado
def cria_posicao(coluna,linha):
    if isinstance (coluna,int) and isinstance (linha,int):
        return (coluna,linha)
    else:
        raise ValueError ('Valores inválidos')

#==========================================================
#SELECTORES
#==========================================================

#coluna: posicao -> inteiro 
#coluna(posicao) tem o valor da coluna da posição dada
def coluna(posicao):
    return posicao[0]

#linha: posicao -> inteiro
#linha(posicao) tem o valor da linha da posição dada
def linha(posicao):
    return posicao[1]

#==========================================================
#RECONHECEDORES
#==========================================================

#posicao_p: posicao -> logico
#Apresenta True se a posição dada é úma posição válida, False
#caso contrário
def posicao_p(posicao):
    return isinstance (posicao,tuple) and len(posicao) == 2 and isinstance (posicao[0],int) and isinstance (posicao[1],int)

#==========================================================
#TESTES
#==========================================================

#posicoes_iguais: posicao x posicao -> logico
#Apresenta True se as posições dadas são iguais, False caso
#contrário.
def posicoes_iguais(pos1,pos2):
    return pos1 == pos2

#==========================================================
#OPERACOES
#==========================================================

