#Nomes
#Filipe Alexandre Duarte Fernandes n�73253
#Miguel Alexandre Louren�o Santos n�75551
#Tom�s Almeida e Silva Martins Alves n�75541

# IMPORTAR O FICHEIRO NASA
from NASA import *
           
# Fun��o base
def temperaturas(colunaInicial,linhaInicial):  
    def validarArgumentos(cI,lI):
        if cI < 0 or cI > x:
            return False
        elif lI < 0 or lI > y:
            return False
        else:
            return True         

    def test_pos_hor(cI,lI):
        # Se estiver � esquerda da coluna central
        if (cI < x//2):
            return 1
        # Se estiver � direita da coluna central
        elif (cI > x//2):
            return -1
        # Se estiver na coluna central
        else:
            return 0
   
        # Para definir a m�dia da temperatura num ponto caso o seu conteudo d� ' '
    def media_ponto(cI,lI):
        contador = 0
        soma_para_a_media = 0
        # J� funciona para os limites e para ' '
        # Para calcular a parte de cima dos '8 malditos'
        for i in range(cI-1, cI+2):
            if (i < x and i > 0) and (lI != y):
                if conteudo(i,lI+1) != ' ':              
                    soma_para_a_media = soma_para_a_media + conteudo(i,lI+1)
                    contador = contador + 1
        # Para calcular a parte do meio dos '8 malditos'
        for i in range(cI-1, cI+2):
            if (i < x and i > 0) and (lI > 0 and lI <= y):
                if conteudo(i,lI) != ' ':
                    soma_para_a_media = soma_para_a_media + conteudo(i,lI)
                    contador = contador + 1
        # Para calcular a parte de baixo dos '8 malditos'
        for i in range(cI-1, cI+2):
            if (i < x and i > 0) and (lI != 0):
                if conteudo(i,lI-1) != ' ':
                    soma_para_a_media = soma_para_a_media + conteudo(i,lI-1)
                    contador = contador + 1
        if contador != 0:
            return soma_para_a_media/contador
        else:
            return soma_para_a_media   
   
    def test_pos_ver(cI,lI,y):
        # Se estiver abaixo ou ser (d)a linha central
        if lI <= y//2:
            return 1
        # Se estiver acima da linha central
        elif lI > y//2:
            return -1
    
    def movimento_horizontal(cI,lI,x,m,contaPontos,somaTemperaturas):
        temperatura_anterior = 0
        # Movimento Horizontal
        # Se m for 1: movimeto para a direita
        # Se m for -1: movimento para a esquerda
        for i in range(cI,x//2+1,m):
            somaTemperaturas = somaTemperaturas + temperatura_ponto(cI,lI)
            contaPontos = contaPontos + 1
            temperatura_anterior = temperatura_ponto(cI,lI)
        t_1 = [somaTemperaturas, contaPontos, temperatura_anterior]
        return t_1   
            
    def movimento_vertical(cI,lI,y,n,temperatura_anterior,ponto_final,contaPontos,somaTemperaturas):    
        # Movimento Vertical:
        # Se n for 1: movimento para cima
        # Se n for -1: movimento para baixo
        linhaFinal = linhaInicial
        for i in range(linhaInicial,y//2+1,n):
            somaTemperaturas = somaTemperaturas + temperatura_ponto(cI,lI)
            contaPontos = contaPontos + 1
            temperatura_anterior = temperatura_ponto(cI,lI)
            linhaFinal = linhaFinal + n
        ponto_final = (x//2,linhaFinal)
        t_2 = [somaTemperaturas, contaPontos, ponto_final]
        return t_2
    
    def temperatura_ponto(cI,lI):
            c = conteudo(cI,lI)
            if c != ' ':
                return c
            else:
                m = media_ponto(cI,lI)
                if m != 0:
                    return m
                else:
                    return temperatura_anterior
            
    # colunaInicial e linhaInicial correspondem � posi��o inicial
    dimensoes_mapa = dimensoes()
    x = dimensoes_mapa[0] # N�mero de colunas
    y = dimensoes_mapa[1] # N�mero de linhas
    cI = colunaInicial
    lI = linhaInicial
    somaTemperaturas = 0
    contaPontos = 1
    temperatura_anterior = 0
    pontosSemTemperatura = []
    posicao_inicial = (cI,lI)
    ponto_final = ( )
    mudanca_direcao = (x//2,lI)    
    
    if validarArgumentos(cI,lI):
        t_1 = movimento_horizontal(cI,lI,x,test_pos_hor(cI,lI),contaPontos,somaTemperaturas)        
        t_2 = movimento_vertical(cI,lI,y,test_pos_ver(cI,lI,y),temperatura_anterior,(),contaPontos,somaTemperaturas)
        somaTemperaturas = t_1[0] + t_2[0]
        contaPontos = t_1[1] + t_2[1]
        ponto_final = t_2[2]
        return [posicao_inicial, mudanca_direcao, ponto_final, somaTemperaturas/contaPontos, pontosSemTemperatura]
    else:
        raise ValueError('Os argumentos est�o errados.') 