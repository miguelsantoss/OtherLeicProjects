#Nomes
#Filipe Alexandre Duarte Fernandes nº73253
#Miguel Alexandre Lourenço Santos nº75551
#Tomás Almeida e Silva Martins Alves nº75541

# IMPORTAR O FICHEIRO NASA
from NASA import *
           
# Função base
def temperaturas(colunaInicial,linhaInicial):
    # Nota de Alteração: se os valores estão na função base, são conhecidos nesta
    def validarArgumentos():
        if colunaInicial < 0 or colunaInicial > x:
            return False
        elif linhaInicial < 0 or linhaInicial > y:
            return False
        else:
            return True         

    # Nota de Alteração: se os valores estão na função base, são conhecidos nesta
    def test_pos_hor():
        # Se estiver à esquerda da coluna central
        if (colunaInicial < x//2):
            return 1
        # Se estiver à direita da coluna central
        elif (colunaInicial > x//2):
            return -1
        # Se estiver na coluna central
        else:
            return 0

    # Nota de Alteração: se os valores estão na função base, são conhecidos nesta; e não é precisa a informação da coluna
    def test_pos_ver():
        # Se estiver abaixo ou ser (d)a linha central
        if linhaInicial <= y//2:
            return 1
        # Se estiver acima da linha central
        elif linhaInicial > y//2:
            return -1
   
    # Nota de Alteração: aqui já não é coluna inicial, nem linha inicial, é para qualquer ponto do caminho
    def temperatura_ponto(coluna,linha):
            temperaturaLida = conteudo(coluna,linha)
            if temperaturaLida != ' ':
                return temperaturaLida
            else:
                temperaturaMedia = media_ponto(coluna,linha)
                if temperaturaMedia != 0:
                    pontosSemTemperatura.append(((coluna, linha), temperaturaMedia))
                    return temperaturaMedia
                else:
                    pontosSemTemperatura.append(((coluna, linha), temperatura_anterior))
                    return temperatura_anterior

    # Nota de Alteração: aqui já não é coluna inicial, nem linha inicial, é para qualquer ponto do caminho
    # Para definir a média da temperatura num ponto caso o seu conteudo dê ' '
    def media_ponto(coluna, linha):
        # Lista para guardar os pontos válidos para o cálculo da média
        pontos = []

        # Para calcular a parte de cima dos '8 malditos'
        # Nota de Alteração: deve verificar desde logo se a linha de cima é para ler ou não
        # Nota de Alteração: é mais perceptível por linha < y do que linha != y
        # Nota de Alteração: não esqueçam que se a altura é 10, então as linhas são 0,1,2,...,7,8,9 
        if linha + 1 < y:
            for i in range(coluna - 1, coluna + 2):
                if i < x and i > 0:
                    pontos.append((i, linha + 1))

        # Para calcular a parte do meio dos '8 malditos'
        # Nota de alteração: não calculem o próprio ponto, aí já sabem que não há valor
        if linha < y:
            if coluna > 0:
                pontos.append((coluna - 1, linha))
            if coluna + 1 < x:
                pontos.append((coluna + 1, linha))

        # Para calcular a parte de baixo dos '8 malditos'
        if linha - 1 >= 0:
            for i in range(coluna - 1, coluna + 2):
                if i < x and i > 0:
                    pontos.append((i, linha - 1))

        # Agora faz o cálculo da média
        contador = 0
        soma_para_a_media = 0

        for ponto in pontos:
            temperaturaLida = conteudo(ponto[0], ponto[1])
            if temperaturaLida != ' ':              
                soma_para_a_media = soma_para_a_media + temperaturaLida
                contador = contador + 1

        if contador != 0:
            return soma_para_a_media/contador
        else:
            return soma_para_a_media   
   
    def movimento_horizontal(m):
        # Movimento Horizontal
        # Se m for 1: movimento para a direita
        # Se m for -1: movimento para a esquerda
        # Nota de Alteração: isto não funciona se o m for negativo
        # experimentem testar estes dois códigos
        # ">>> for i in range(3, 1, -1): i" e "for i in range(1, 3, -1): i"
        inicio = 0
        fim = 0
        if m == 1:
            inicio = colunaInicial
            fim = x//2 + 1
        elif m == -1:
            inicio = x//2
            fim = colunaInicial - 1
        # se não vai andar na horizontal, é preciso pelo menos ler a temperatura neste ponto
        elif m == 0:
            m = 1
            inicio = colunaInicial
            fim = inicio + 1
            
        somaTemperaturas = 0
        contaPontos = 0
        temperatura_anterior = 0

        for i in range(inicio, fim, m):
            temperaturaPonto = temperatura_ponto(i, linhaInicial)
            somaTemperaturas = somaTemperaturas + temperaturaPonto
            contaPontos = contaPontos + 1
            temperatura_anterior = temperaturaPonto
            
        t_1 = [somaTemperaturas, contaPontos, temperatura_anterior]
        return t_1   
            
    def movimento_vertical(n, temperatura_anterior):    
        # Movimento Vertical:
        # Se n for 1: movimento para cima
        # Se n for -1: movimento para baixo
        # Nota de alteração: atenção para não lerem o ponto de mudança duas vezes! Já foi lido na outra função
        inicio = 0
        fim = 0
        ponto_final = ()
        if n == 1:
            inicio = linhaInicial + 1
            fim = y
            ponto_final = (x//2, y - 1)
        elif n == -1:
            inicio = y - 1
            fim = -1
            ponto_final = (x//2, 0)

        somaTemperaturas = 0
        contaPontos = 0
        temperatura_anterior = 0

        for i in range(inicio, fim, n):
            temperaturaPonto = temperatura_ponto(x//2, i)
            somaTemperaturas = somaTemperaturas + temperaturaPonto
            contaPontos = contaPontos + 1
            temperatura_anterior = temperaturaPonto

        t_2 = [somaTemperaturas, contaPontos, ponto_final]
        return t_2
    
            
    # colunaInicial e linhaInicial correspondem à posição inicial
    dimensoes_mapa = dimensoes()
    x = dimensoes_mapa[0] # Número de colunas
    y = dimensoes_mapa[1] # Número de linhas
    
    if validarArgumentos():
        pontosSemTemperatura = []
        
        t_1 = movimento_horizontal(test_pos_hor())        
        t_2 = movimento_vertical(test_pos_ver(), t_1[2])

        somaTemperaturas = t_1[0] + t_2[0]
        contaPontos = t_1[1] + t_2[1]

        posicao_inicial = (colunaInicial, linhaInicial)
        mudanca_direcao = (x//2, linhaInicial)    
        ponto_final = t_2[2]

        return [posicao_inicial, mudanca_direcao, ponto_final, somaTemperaturas/contaPontos, pontosSemTemperatura]
    else:
        raise ValueError('Os argumentos estão errados.') 
