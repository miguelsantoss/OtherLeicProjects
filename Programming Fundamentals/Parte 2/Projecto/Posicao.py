#==========================================================
#DEFINICAO DE POSICAO
#==========================================================

class posicao:
    def __init__(self,coluna,linha):
        if isinstance (coluna,int) and isinstance (linha,int):
            self.coluna = coluna
            self.linha = linha
            self.posicao = (self.coluna,self.linha)
        else:
            raise TypeError('Os argumentos nao sao validos')
    
    def p_coluna(self):
        return self.posicao[0]
    
    def p_linha (self):
        return self.posicao[1]
    
    def posicao_coluna (self):
        return self.posicao[0]
    
    def posicao_linha (self):
        return self.posicao[1]
    
    def __eq__(self,outro):
        return self.coluna == outro.p_coluna() and self.linha == outro.p_linha
    
    def posicao_relativa(self,direcao):
        if direcao == norte:
            self.posicao = (self.coluna,self.linha + 1)
        if direcao == sul:
            self.posicao = (self.coluna,self.linha - 1)
        if direcao == este:
            self.posicao = (self.coluna + 1,self.linha)
        if direcao == oeste:
            self.posicao = (self.coluna - 1,self.linha)
            


#DESCRIÇAO


#==========================================================
#CONSTRUTORES
#==========================================================

#cria_posicao: inteiro, inteiro -> posicao
#cria_posicao(coluna,linha) tem como valor uma posicao com o numero de colunas e linhas dado
def cria_posicao(coluna,linha):
    if isinstance (coluna,int) and isinstance (linha,int):
        return (coluna,linha)
    else:
        raise ValueError ('Valores invalidos')

#==========================================================
#SELECTORES
#==========================================================

#coluna: posicao -> inteiro 
#coluna(posicao) tem o valor da coluna da posicao dada
def posicao_coluna(posicao):
    return posicao[0]

#linha: posicao -> inteiro
#linha(posicao) tem o valor da linha da posicao dada
def posicao_linha(posicao):
    return posicao[1]

#==========================================================
#RECONHECEDORES
#==========================================================

#posicao_p: posicao -> logico
#Apresenta True se a posicao dada e uma posicao valida, False
#caso contrario
def posicao_p(posicao):
    return isinstance (posicao,tuple) and len(posicao) == 2 and isinstance (posicao[0],int) and isinstance (posicao[1],int)

#==========================================================
#TESTES
#==========================================================

#posicoes_iguais: posicao x posicao -> logico
#Apresenta True se as posicoes dadas sao iguais, False caso
#contrario.
def posicoes_iguais(pos1,pos2):
    return pos1 == pos2