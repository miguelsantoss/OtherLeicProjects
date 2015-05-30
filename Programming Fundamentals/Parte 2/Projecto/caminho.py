class caminho:
    def __init__(self,posicao):
        self.caminho = [posicao]
    
    def caminho_junta_posicao(self,posicao):
        self.caminho = self.caminho + [posicao]
        
    def caminho_origem(self):
        return self.caminho[0]
    
    def caminho_apos_origem(self):
        if len(self.caminho)=1:
            raise ValueError ('Caminho apenas tem uma posicao')
        else:
            return self.caminho[1]
    
    def caminho_destino(self):
        return self.caminho[-1]
    
    def caminho_antes_destino(self):
        if len(self.caminho)=1:
            raise ValueError ('Caminho apenas tem uma posicao')        
        else:
            return self.caminho[-2]
    