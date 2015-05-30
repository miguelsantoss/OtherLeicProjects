# = = = PROJECTO DE FP - 2a parte = = = #
#
#  - Grupo 027 - 
# 
# . Aluno 73253 - Filipe Alexandre Duarte Fernandes
# . Aluno 75541 - Tomas Almeida da Silva Alves
# . Aluno 75551 - Miguel Alexandre Lourenco Santos

# = = = Modulos exteriores = = = # 

from robot import * # Modulo de comunicacao com o robot
# < Incluir aqui outros imports que ache necessarios >

# = = = Definicao de tipos = = = #

# - - Tipo objecto - - #
# ========================================================================
# CONSTRUTORES
# ========================================================================

espaco = 'espaco'
comida = 'comida'
premio = 'premio'
monstro = 'monstro'
parede = 'parede'
desconhecido = 'desconhecido'

# ========================================================================
#RECONHECEDORES
# ========================================================================
#Os reconhecedores apresentam o valor logico true se o objecto dado for do tipo pretendido. Por exemplo, espaco_p: objecto -> logico. Este reconhecedor ira devolver o valor true se e so se o objeto dado for 'espaco'.

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

# ========================================================================
# TESTES
# ========================================================================
#A funcao objectos_iguais devolve o valor true quando ambos os objectos dados sao iguais.
#objectos_iguais: objecto1 x objecto2 -> logico
def objectos_iguais(obj1, obj2):
    return obj1 == obj2


# - - Tipo direccao - - #

# ========================================================================
# CONSTRUTORES
# ========================================================================
norte = 'norte'
sul = 'sul'
este = 'este'
oeste = 'oeste'

# ========================================================================
# RECONHECEDORES
# ========================================================================
#Os reconhecedores apresentam o valor logico true se a direccao dada for do tipo pretendido. Por exemplo, norte_p: direccao -> logico. Este reconhecedor ira devolver o valor true se e so se a direccao dada for 'norte'.

def norte_p (direcao):
    return isinstance (direcao,str) and direcao == norte


def sul_p (direcao):
    return isinstance (direcao,str) and direcao == sul


def este_p (direcao):
    return isinstance (direcao,str) and direcao == este


def oeste_p (direcao):
    return isinstance (direcao,str) and direcao == oeste

# ========================================================================
# TESTES
# ========================================================================
#A funcao direccoes_iguais devolve o valor logico true apenas quando as duas direccoes dadas sao iguais.
#direccoes_iguais: direcao1 x direcao2 -> logico

def direcoes_iguais (direcao1,direcao2):
    return direcao1 == direcao2

# ========================================================================
# MODIFICADOR
# ========================================================================

#vira_esquerda: direcao -> direcao
#vira_esquerda(direcao) recebe uma direcao e dvolve a direcao que se encontra imediatamente a sua esquerda
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
#vira_direita(direcao) recebe uma direcao e devolve a direcao que se encontra imediatamente a sua direita
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


# - - Tipo posicao - - #

class posicao:
    # ========================================================================
    # CONSTRUTORES
    # ========================================================================
    #O metodo __init__ ira criar um objecto posicao com a linha e a coluna dadas
    def __init__(self,linha,coluna):
        if isinstance (coluna,int) and isinstance (linha,int):
            self.coluna = coluna
            self.linha = linha
        else:
            raise TypeError('Os argumentos nao sao validos')
        

    # ========================================================================
    # SELECTORES
    # ========================================================================
    #Os selectores irao retornar a linha ou a coluna do objecto posicao atraves dos metodos posicao_linha e posicao_coluna, respectivamente
    def posicao_coluna (self):
        return self.coluna
        
    def posicao_linha (self):
        return self.linha

    # ========================================================================
    # TESTES
    # ========================================================================
    #Este metodo ira devolver o valor true se e so se ambos os objectos posicao dados tiverem o mesmo valor da linha e o mesmo valor da coluna
    def posicao_igual(self,outro):
        return self.coluna == outro.posicao_coluna() and self.linha == outro.posicao_linha()
          
    # ========================================================================
    # MODIFICADOR
    # ========================================================================
    #O metodo posicao_relativa recebe uma direcao e devolve a posicao adjacente nessa direcao
    def posicao_relativa(self,direcao):
        if direcao == norte:
            return posicao(self.linha - 1, self.coluna)

        elif direcao == sul:
            return posicao(self.linha + 1, self.coluna)
        
        elif direcao == este:
            return posicao(self.linha, self.coluna + 1)
        
        elif direcao == oeste:
            return posicao(self.linha, self.coluna - 1)        

    # ========================================================================
    # TRANSFORMADORES DE SAIDA
    # ========================================================================
    #Este metodo ira ser utilizado na representacao do objecto posicao. Considerou-se a representacao deste como um tuplo em que o primeiro valor e a linha e o segundo valor e a coluna.
    def __repr__(self):
        return str('(') + str(self.linha) + str(',') + str(self.coluna) + str(')')

# - - Tipo mapa - - #

class mapa:
    # ========================================================================
    # CONSTRUTORES
    # ========================================================================    
    
    def __init__(self):
        self.mapa = {}
    
    def mapa_poe_objecto_em (self,posicao,objecto):
        self.mapa[(posicao.posicao_linha(),posicao.posicao_coluna())] = objecto
        return self
    
    # ========================================================================
    # SELECTORES
    # ========================================================================    

    def mapa_objecto_em (self,posicao):
        if (posicao.posicao_linha(),posicao.posicao_coluna()) in self.mapa:
            return self.mapa[(posicao.posicao_linha(),posicao.posicao_coluna())]
        else:
            return desconhecido

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

    # ========================================================================
    # TRANSFORMADORES DE SAIDA
    # ========================================================================                
    
    def __repr__(self):
        return str(self.mapa)


# - - Tipo caminho - - #

class caminho:
    # ========================================================================
    # CONSTRUTORES
    # ========================================================================    
    
    def __init__(self,posicao):
        self.caminho = [posicao]
    
    def caminho_junta_posicao(self,direcao):
        if direcao == norte:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha() - 1,self.caminho[-1].posicao_coluna())]
        elif direcao == sul:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha() + 1,self.caminho[-1].posicao_coluna())]
        elif direcao == este:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha(),self.caminho[-1].posicao_coluna() + 1)]
        elif direcao == oeste:
            self.caminho = self.caminho + [posicao(self.caminho[-1].posicao_linha(),self.caminho[-1].posicao_coluna() - 1)]
        elif isinstance(direcao,posicao):
            self.caminho = self.caminho + direcao
        return self
    
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


    # ========================================================================
    # SELECTORES
    # ========================================================================
            
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
    
    # ========================================================================
    # TESTE
    # ========================================================================    
    
    def caminho_contem_ciclo (self): 
        for i in self.caminho:
            for k in self.caminho:
                if i.posicao_igual(k) and i != k:
                    return True
        return False


# - - Tipo estado - - #

class estado:
    # ========================================================================
    # CONSTRUTORES
    # ========================================================================    
    
    def __init__(self,posicao,direcao):
        self.posicao = posicao
        self.direcao = direcao
        self.mapa = mapa()
        self.mapa = self.mapa.mapa_poe_objecto_em(self.posicao,espaco)
        self.caminho = caminho(posicao)

    # ========================================================================
    # MODIFICADOR
    # ========================================================================

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

    # ========================================================================
    # SELECTORES
    # ========================================================================
    
    def estado_posicao_robot(self):
        return self.posicao

    def estado_direccao_robot(self):
        return self.direcao
    
    def estado_mapa(self):
        return self.mapa
    
    def estado_caminho_percorrido(self):
        return self.caminho.caminho_elimina_ciclos()

# = = = Controlo do Robot = = = #

# controla_robot : robot -> str x estado
#
# controla_robot(e, r) deve, com base no seu estado interno, escolher e executar
# uma accao sobre o robot r, e actualizar o estado em conformidade.

def controla_robot(e, r):
    def robot_nao_conhece():
        if robot_sente_espaco(e):
            robot_anda(e)
            r.estado_robot_avanca()
            return e
            
        if robot_sente_parede(e):        
                
            r.mapa.mapa_poe_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(r.estado_direccao_robot()),parede)
                
            if r.estado_direccao_robot() == este and r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(norte)) == desconhecido:
                robot_vira_esquerda(e)
                r.estado_robot_vira_esquerda()
                return e
                
            if r.estado_direccao_robot() == este and (r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(sul)) == desconhecido or r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(sul)) == parede):
                robot_vira_direita(e)
                r.estado_robot_vira_direita()
                return e
                
            if r.estado_direccao_robot() == este and r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(oeste)) == desconhecido:
                robot_vira_esquerda(e)
                r.estado_robot_vira_esquerda()                
                robot_vira_esquerda(e) 
                r.estado_robot_vira_esquerda()
                return e
            
            if r.estado_direccao_robot() == norte and r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(oeste)) == desconhecido:
                robot_vira_esquerda(e)
                r.estado_robot_vira_esquerda()
                return e
    
            if r.estado_direccao_robot() == norte and (r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(este)) == desconhecido or r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(este)) == parede):
                robot_vira_direita(e)
                r.estado_robot_vira_direita()
                return e
                
            if r.estado_direccao_robot() == norte and r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(sul)) == desconhecido:
                robot_vira_esquerda(e)
                r.estado_robot_vira_esquerda()                
                robot_vira_esquerda(e) 
                r.estado_robot_vira_esquerda()
                return e
            
            if r.estado_direccao_robot() == oeste and (r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(sul)) == desconhecido or r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(norte)) == parede):
                robot_vira_esquerda(e)
                r.estado_robot_vira_esquerda()
                return e
            
            if r.estado_direccao_robot() == oeste and r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(norte)) == desconhecido:
                robot_vira_direita(e)
                r.estado_robot_vira_direita()
                return e
            
            if r.estado_direccao_robot() == oeste and r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(este)) == desconhecido:
                robot_vira_esquerda(e)
                r.estado_robot_vira_esquerda()                
                robot_vira_esquerda(e) 
                r.estado_robot_vira_esquerda()
                return e
                
            if r.estado_direccao_robot() == sul and (r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(este)) == desconhecido or r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(oeste)) == parede):
                robot_vira_esquerda(e)
                r.estado_robot_vira_esquerda()
                return e
            
            if r.estado_direccao_robot() == sul and r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(oeste)) == desconhecido:
                robot_vira_direita(e)
                r.estado_robot_vira_direita()
                return e
                
            if r.estado_direccao_robot() == sul and r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(norte)) == desconhecido:
                robot_vira_esquerda(e)
                r.estado_robot_vira_esquerda()                
                robot_vira_esquerda(e) 
                r.estado_robot_vira_esquerda()
                return e
            
        if robot_sente_monstro(e):
            robot_dispara(e)
            robot_anda(e)
            r.estado_robot_avanca()
            r.estado_robot_dispara()
            return e
        
        if robot_sente_premio(e) or robot_sente_comida(e):
            robot_apanha(e)
            robot_anda(e)
            r.estado_robot_avanca()
            r.estado_robot_apanha()
            return e    
    
    def robot_conhece():        
            if r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(r.estado_direccao_robot())) != parede:
                robot_anda(e)
                r.estado_robot_avanca()
                return e
            
            if r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(r.estado_direccao_robot())) == parede:
                if r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(vira_direita(r.estado_direccao_robot()))) == parede:
                    robot_vira_esquerda(e)
                    r.estado_robot_vira_esquerda()
                elif r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(vira_esquerda(r.estado_direccao_robot()))) == parede:
                    robot_vira_direita(e)
                    r.estado_robot_vira_direita()
                else:
                    robot_vira_direita(e)
                    r.estado_robot_vira_direita()                
                return e
        
        
    if r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(vira_direita(r.estado_direccao_robot()))) == desconhecido:
        robot_vira_direita(e)
        r.estado_robot_vira_direita()
        robot_nao_conhece()
    
    elif r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(vira_esquerda(r.estado_direccao_robot()))) == desconhecido:
            robot_vira_esquerda(e)
            r.estado_robot_vira_esquerda()
            robot_nao_conhece()    
    
    elif r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(r.estado_direccao_robot())) == desconhecido:
        robot_nao_conhece()
    
    elif r.mapa.mapa_objecto_em(posicao(r.estado_posicao_robot().posicao_linha(),r.estado_posicao_robot().posicao_coluna()).posicao_relativa(vira_direita(r.estado_direccao_robot()))) != desconhecido:
        robot_conhece()
        
    
    
            

import time
def teste_controlo(fich):
    canal_comunicacao = inicia_comunicacao()
    e = estado(posicao(1,1),este)
    while robot_energia(canal_comunicacao) > 0:
        time.sleep(0.1)
        controla_robot(canal_comunicacao,e)
        print('energia: ',robot_energia(canal_comunicacao))
        canal_comunicacao._Robot__e = 100
    robot_desliga(canal_comunicacao)
    return e.estado_mapa()