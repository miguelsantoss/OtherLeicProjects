class posicao:
    def __init__(self,linha,coluna):
        if isinstance (coluna,int) and isinstance (linha,int):
            self.coluna = coluna
            self.linha = linha
            self.posicao = (self.linha,self.coluna)
        else:
            raise TypeError('Os argumentos nao sao validos')
            
    def p_coluna(self):
        return self.posicao[1]
            
    def p_linha (self):
        return self.posicao[0]
            
    def posicao_coluna (self):
        return self.posicao[1]
        
    def posicao_linha (self):
        return self.posicao[0]
            
    def posicao_igual(self,outro):
        return self.coluna == outro.p_coluna() and self.linha == outro.p_linha()
          
    def posicao_relativa(self,direcao):
        if direcao == norte:
            self.posicao = (self.linha + 1,self.coluna)

        elif direcao == sul:
            self.posicao = (self.linha - 1,self.coluna)

        elif direcao == este:
            self.posicao = (self.linha,self.coluna + 1)

        elif direcao == oeste:
            self.posicao = (self.linha,self.coluna - 1)
        
        return self.posicao