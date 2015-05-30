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