from robot import *

espaco = 'espaco'
comida = 'comida'
premio = 'premio'
monstro = 'monstro'
parede = 'parede'
desconhecido = 'desconhecido'

def espaco_p(obj):
    return isinstance (obj,str) and obj == espaco

def comida_p(obj):
    return isinstance (obj,str) and obj == comida

def premio_p(obj):
    return isinstance (obj,str) and obj == premio

def monstro_p(obj):
    return isinstance (obj,str) and obj == monstro


def parede_p(obj):
    return isinstance (obj,str) and obj == parede


def desconhecido_p(obj):
    return isinstance (obj,str) and obj == desconhecido


def objectos_iguais(obj1, obj2):
    return obj1 == obj2

norte = 'norte'
sul = 'sul'
este = 'este'
oeste = 'oeste'

def norte_p (direcao):
    return isinstance (direcao,str) and direcao == norte


def sul_p (direcao):
    return isinstance (direcao,str) and direcao == sul


def este_p (direcao):
    return isinstance (direcao,str) and direcao == este


def oeste_p (direcao):
    return isinstance (direcao,str) and direcao == oeste


def direcoes_iguais (direcao1,direcao2):
    return direcao1 == direcao2


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


class posicao:
    def __init__(self,linha,coluna):
        if isinstance (coluna,int) and isinstance (linha,int):
            self.coluna = coluna
            self.linha = linha
        else:
            raise TypeError('Os argumentos nao sao validos')
        
    def posicao_coluna (self):
        return self.coluna
        
    def posicao_linha (self):
        return self.linha
            
    def posicao_igual(self,outro):
        return self.coluna == outro.posicao_coluna() and self.linha == outro.posicao_linha()
          
    def posicao_relativa(self,direcao):
        if direcao == norte:
            return posicao(self.linha + 1,self.coluna)

        elif direcao == sul:
            return posicao(self.linha - 1,self.coluna)

        elif direcao == este:
            return posicao(self.linha,self.coluna + 1)

        elif direcao == oeste:
            return posicao(self.linha,self.coluna - 1)        
    
    def __repr__(self):
        return str('(') + str(self.linha) + str(',') + str(self.coluna) + str(')')
    
class mapa:
    def __init__(self):
        self.mapa = {}
    
    def mapa_poe_objecto_em (self,posicao,objecto):
        self.mapa[(posicao.posicao_linha(),posicao.posicao_coluna())] = objecto
        return self
    
    def mapa_objecto_em (self,posicao):
        return self.mapa[(posicao.posicao_linha(),posicao.posicao_coluna())]
    
    def mapa_altura(self):
        altura = 0
        for i in self.mapa:
            if i[0] > altura:
                altura = i[0] + 1
        return altura
    
    def mapa_largura(self):
        largura = 0
        for i in self.mapa:
            if i[1] > largura:
                largura = i[1] + 1
        return largura
                
    def __repr__(self):
        return str(self.mapa)


class caminho:
    def __init__(self,posicao):
        self.caminho = [posicao]
    
    def caminho_junta_posicao(self,direcao):
        if direcao == norte:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha() + 1,self.caminho[-1].posicao_coluna())]
        elif direcao == sul:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha() - 1,self.caminho[-1].posicao_coluna())]
        elif direcao == este:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha(),self.caminho[-1].posicao_coluna() + 1)]
        elif direcao == oeste:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha(),self.caminho[-1].posicao_coluna() - 1)]
        return self
            
    def caminho_origem (self):
        return self.caminho[0]

    def caminho_apos_origem (self):
        if len(self.caminho) > 1:
            novo_caminho = caminho(self.caminho[1])
            for pos in self.caminho[2:]:
                novo_caminho = novo_caminho.caminho_junta_posicao(pos)
            return novo_caminho
        else:
            raise ValueError ('O Caminho tem apenas 1 posicao')

    def caminho_destino (self):
        return self.caminho[-1]
    
    def caminho_antes_destino (self):
        if len(self.caminho) > 1:
            novo_caminho = caminho(self.caminho[0])
            for pos in self.caminho[:-2]:
                novo_caminho = novo_caminho.caminho_junta_posicao(pos)
            return novo_caminho        
        else:
            raise ValueError ('O Caminho tem apenas 1 posicao')
    
    def caminho_comprimento (self):
        return len(self.caminho)
    
    def caminho_contem_ciclo (self): 
        for i in self.caminho:
            for k in self.caminho:
                if i.posicao_igual(k) and i != k:
                    return True
        return False
    
    def caminho_elimina_ciclos (self):
        self.novo_caminho_sem_ciclos = self.caminho
        y = 0
        for i in self.caminho:
            x = 0            
            for k in self.caminho:
                if i.posicao_igual(k)  and i != k:
                    del(self.novo_caminho_sem_ciclos[y:x])
                x = x + 1
            y = y + 1
        return self
    
    # IDEIA: utilizar o self.destino. quando ele contar um igual, ao fim de um for de K, sobe 1 num contador, se for dois ou mais, apenas mete um!!!!!!!!!!!!!!!!!!!
    
    # OUTRA IDEIA: Faz o i a ir de ca para la e o k a vir de la para ca.      O i a partir de [1:] e o k de destino ate 0.
    def __repr__(self):
        return str('caminho:[ ') + str(self.caminho) + str(' ]')
    
class estado:
    def __init__(self,posicao,direcao):
        self.posicao = posicao
        self.direcao = direcao
        self.mapa = mapa()
        self.mapa = self.mapa.mapa_poe_objecto_em(self.posicao,espaco)
        self.caminho = caminho(posicao)

    def estado_robot_avanca(self):
        self.posicao = self.posicao.posicao_relativa(self.direcao)
        self.caminho = self.caminho.caminho_junta_posicao(self.direcao)
        self.mapa = self.mapa.mapa_poe_objecto_em(self.posicao,espaco)

        return self
        
    def estado_robot_vira_direita(self):
        self.direcao = vira_direita(self.direcao)
        return self
    
    def estado_robot_vira_esquerda(self):
        self.direcao = vira_esquerda(self.direcao)
        return self
    
    def estado_robot_apanha(self):
        if robot_sente_premio == True:
            self.mapa = self.mapa.mapa_poe_objecto_em(self.posicao.posicao_relativa(self.direcao),premio)
        elif robot_sente_comida == True:
            self.mapa = self.mapa.mapa_poe_objecto_em(self.posicao.posicao_relativa(self.direcao),comida)
        return self
        
    def estado_robot_dispara(self):
        self.mapa = self.mapa.mapa_poe_objecto_em(self.posicao.posicao_relativa(self.direcao),monstro)
        return self
    
    def estado_posicao_robot(self):
        return self.posicao
    
    def estado_direccao_robot(self):
        return self.direcao
    
    def estado_mapa(self):
        return self.mapa
    
    def estado_caminho_percorrido(self):
        return self.caminho.caminho_elimina_ciclos()
