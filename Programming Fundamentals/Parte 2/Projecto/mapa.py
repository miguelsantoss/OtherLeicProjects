class mapa:
    def __init__(self):
        self.mapa = []
    
    def mapa_poe_objecto_em(self,posicao,objecto):
        self.mapa = self.mapa + [[posicao] + [objecto]]
        return self.mapa
    
    def mapa_objecto_em(self,posicao):
        for i in self.mapa:
            if self.mapa[i][0] == posicao:
                return self.mapa[i][1]
    
    def mapa_altura(self):
        self.altura = 0
        for i in self.mapa:
            if self.mapa[i][0][0] > self.altura:
                self.altura = self.mapa[i][0][0]
    def mapa_largura(self):
        self.largura = 0
        for i in self.mapa:
            if self.mapa[i][0][1] > self.altura:
                self.altura = self.mapa[i][0][1]    
    