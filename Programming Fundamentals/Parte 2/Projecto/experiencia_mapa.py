def dafuq(dic,posicao):
    return dic[posicao]

class posicao:
    def __init__(self,x,y):
        self.x = x
        self.y = y
    
    def __repr__(self):
        return str('(') + str(self.x) + str(',') + str(self.y) + str(')')
    
def wtf (posicao,x):
    dic = {posicao:x}
    return dic

dic = [1,2,3,4,5,6,7,8,9,10]

