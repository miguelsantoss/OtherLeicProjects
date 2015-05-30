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
#Apresenta o valor True se a direccao dada for "norte",
#apresentando False se a direccao nao for valida ou se nao
#for "norte"
def norte_p (direcao):
    return isinstance (direcao,str) and direcao == norte

#sul_p: direcao -> logico
#Apresenta o valor True se a direccao dada for "sul",
#apresentando False se a direccao nao for valida ou se nao
#for "sul"
def sul_p (direcao):
    return isinstance (direcao,str) and direcao == sul

#este_p: direcao -> logico
#Apresenta o valor True se a direccao dada for "este",
#apresentando False se a direccao nao for valida ou se nao
#for "este"
def este_p (direcao):
    return isinstance (direcao,str) and direcao == este

#oeste_p: direcao -> logico
#Apresenta o valor True se a direccao dada for "oeste",
#apresentando False se a direccao nao for valida ou se nao
#for "oeste"
def oeste_p (direcao):
    return isinstance (direcao,str) and direcao == oeste

#==========================================================
#TESTES
#==========================================================

#direcoes_iguais: direcao1 x direcao2 -> logico
#direcoes_iguais devolve True se as direcoes dadas sao iguais
#devolvendo False caso contrario
def direcoes_iguais (direcao1,direcao2):
    return direcao1 == direcao2

#==========================================================
#OPERACOES
#==========================================================

#vira_esquerda: direcao -> direcao
#vira_esquerda(direccao) recebe uma direccao e devolve a direccao a esquerda
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
#vira_direita(direccao) recebe uma direccao e devolve a direccao a direita
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