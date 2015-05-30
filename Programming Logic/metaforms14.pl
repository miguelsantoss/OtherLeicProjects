%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%       GRUPO NUM: 41
%       ALUNOS: 73253 - Filipe Fernandes;
%               75541 - Tomas Alves; e
%               75551 - Miguel Santos.
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%   PISTAS INTERMEDIAS
%       - apos analisar os resultados possiveis para cada tipo de pista intermedia,
%       concluimos que, para cada posicao relativa da peca nessa pista, esta poderia ser
%       convertida numa pista simples usando essa posicao relativa.
%       - assim, implementamos as pistas intermedias simplificando-as por utilizar as pistas basicas.
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

trioLeft(A, Linha, Coluna, Tabuleiro) :- rectanguloVertical(A, Linha, Coluna, Tabuleiro). 

trioRight(A, Linha, Coluna, Tabuleiro) :- rectanguloVertical(A, Linha, Coluna, Tabuleiro).

cobra(A, Linha, Coluna, Tabuleiro) :- rectanguloVertical(A, Linha, Coluna, Tabuleiro).

tSimples(A, Linha, Coluna, Tabuleiro) :- rectanguloHorizontal(A, Linha, Coluna, Tabuleiro).

tLeft(A, Linha, Coluna, Tabuleiro) :- rectanguloVertical(A, Linha, Coluna, Tabuleiro).

tRight(A, Linha, Coluna, Tabuleiro) :- rectanguloVertical(A, Linha, Coluna, Tabuleiro).

tInvertido(A, Linha, Coluna, Tabuleiro) :- rectanguloHorizontal(A, Linha, Coluna, Tabuleiro).

cantoTopLeft(A, Linha, Coluna, Tabuleiro) :- quadrado(A, Linha, Coluna, Tabuleiro).

cantoTopRight(A, Linha, Coluna, Tabuleiro) :- quadrado(A, Linha, Coluna, Tabuleiro).

cantoBottomLeft(A, Linha, Coluna, Tabuleiro) :- quadrado(A, Linha, Coluna, Tabuleiro).

cantoBottomRight(A, Linha, Coluna, Tabuleiro) :- quadrado(A, Linha, Coluna, Tabuleiro).

diagonalGrave(A, Linha, Coluna, Tabuleiro) :- quadrado(A, Linha, Coluna, Tabuleiro).

diagonalAguda(A, Linha, Coluna, Tabuleiro) :- quadrado(A, Linha, Coluna, Tabuleiro).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%
%   check/2
%           - para o predicado check funcionar, precisamos de enumerar todas as pecas que
%			podem existir no tabuleiro.
%			
%           - foi implementado um predicado membro/2 que trata de verificar se a peca
%			que recebe como primeiro argumento (com a sua forma e cor especificas) esta presente na lista que recebe como segundo argumento.
%
%           - assim, o predicado check/2 preenche o tabuleiro que recebe
%           como segundo argumento, a partir das pecas do tabuleiro que recebe como primeiro
%           argumento. 
%
%			- Quando este predicado, ao percorrer ao tabuleiro, encontra uma posicao em que a peca correspondente
%			nao esta definida, este procura por uma peca que ainda nao tenha sido colocada, coloca-a nessa posicao,
%			e continua a colocar o restante das pecas.
%
%			- No caso de uma posicao do tabuleiro apenas contiver informacao relativa a cor ou
%           forma, este predicado ira colocar as pecas conforme se ajustem ao tabuleiro incompleto, respeitando as regras.
%
%           - assim, o tabuleiro que corresponde ao segundo argumento deste predicado foi completado com
%           as pecas que faltavam no primeiro, caso faltassem, de forma a manter todas as regras
%           impostas pelas pistas do desafio.
%
%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

peca(triangulo, vermelho).
peca(circulo, vermelho).
peca(quadrado, vermelho).
peca(triangulo, azul).
peca(circulo, azul).
peca(quadrado, azul).
peca(triangulo, amarelo).
peca(circulo, amarelo).
peca(quadrado, amarelo).

membro(X, [Y|T]) :- X == Y; membro(X, T).

check([],[]) :- !.
check([peca(Forma, Cor)|R], [peca(Forma, Cor)|R]) :- peca(Forma, Cor), not(membro(peca(Forma, Cor),R)), check(R, R).