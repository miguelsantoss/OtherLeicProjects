from robot import *
from testes_tai import *
import time
def teste_controlo(fich):
    canal_comunicacao = inicia_comunicacao()
    e = estado(posicao(1,1),este)
    while robot_energia(canal_comunicacao) > 0:
        time.sleep(0.1)
        controla_robot(canal_comunicacao,e)
    robot_desliga(canal_comunicacao)