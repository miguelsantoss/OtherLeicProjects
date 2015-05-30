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
        self.altura = 0
        for i in self.mapa:
            if i[0] > self.altura:
                self.altura = i[0] + 1
        return self.altura
    
    def mapa_largura(self):
        self.largura = 0
        for i in self.mapa:
            if i[1] > self.largura:
                self.largura = i[1] + 1
        return self.largura
                
    def __repr__(self):
        return str(self.mapa)


class caminho:
    def __init__(self,posicao):
        self.caminho = [posicao]
    
    def caminho_junta_posicao(self,direcao):
        if direcao == norte:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha() + 1,self.caminho[-1].posicao_coluna())]
        if direcao == sul:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha() - 1,self.caminho[-1].posicao_coluna())]
        if direcao == este:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha(),self.caminho[-1].posicao_coluna() + 1)]
        if direcao == oeste:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha(),self.caminho[-1].posicao_coluna() - 1)]
        return self
            
    def caminho_origem (self):
        return self.caminho[0]
    
#---->verificar erro
    def caminho_apos_origem (self):
        if not len(self.caminho) < 1:
            return self.caminho[1]
        else:
            raise ValueError ('O Caminho tem apenas 1 posicao')
    
    def caminho_destino (self):
        return self.caminho[-1]
    
    def caminho_antes_destino (self):
        if not len(self.caminho) < 1:
            return self.caminho[-2]
        else:
            raise ValueError ('O Caminho tem apenas 1 posicao')
    
    def caminho_comprimento (self):
        return len(self.caminho)
    
#----->verificar o erro
#nao da erro quando se faz return self
    def caminho_contem_ciclo (self): 
        for i in self.caminho:
            for k in self.caminho:
                if i.posicao_igual(k) and i != k:
                    return True

        
    def caminho_elimina_ciclos (self):
        y = 0
        for i in self.caminho:
            x = 0            
            for k in self.caminho:
                if i.posicao_igual(k)  and i != k:
                    del(self.caminho[y:x])
                x = x + 1
            y = y + 1
        return self 
    
    def __repr__(self):
        return str('caminho:[ ') + str(self.caminho) + str(' ]')
    
class estado:
    def __init__(self,posicao,direcao):
        self.posicao = posicao
        self.direcao = direcao
        self.mapa = mapa()
        self.mapa = self.mapa.mapa_poe_objecto_em(self.posicao,espaco)
        self.caminho = caminho(posicao)

#------>#mete-se espaco?
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
        self.mapa = self.mapa.mapa_poe_objecto_em(self.posicao.posicao_relativa(self.direcao),cenas)
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
    
        
        
    
