; 	ZONA I: Definicao de constants
; 	Pseudo-instrucao : EQU

FIM_TEXTO		EQU 	'@'
IO_DISPLAY_0		EQU	FFF0h
IO_DISPLAY_1		EQU	FFF1h
IO_DISPLAY_2		EQU	FFF2h
IO_DISPLAY_3		EQU	FFF3h
IO_LCD_CONTROL		EQU	FFF4h
IO_LCD_WRITE		EQU	FFF5h
TIMER_VALUE		EQU	FFF6h
TIMER_CONTROL		EQU	FFF7h
IO_LEDS			EQU	FFF8h
INT_MASK_ADDR		EQU	FFFAh
IO_CURSOR		EQU	FFFCh
IO_STATUS 		EQU 	FFFDh
IO_WRITE		EQU 	FFFEh			
IO_READ 		EQU 	FFFFh
SP_INICIAL 		EQU 	FDFFh
MAX_DIR			EQU	164Eh
MAX_ESQ			EQU	1601h
PONT_INICIAL		EQU	1626h
TERRA			EQU	1701h
INT_MASK		EQU	1000100000000111b
TEXTO1 			EQU 	0B18h
TEXTO2			EQU	0D15h
JANELA			EQU	FFFFh
ATIVA_Z			EQU	0018h
TEXTO_MENU		EQU	000Ch
TAM_CANHAO		EQU	0004h
LINHA			EQU	0100h
TEMPO			EQU	0001h
ENABLE_TIMER		EQU	0001h
CONTADOR_MISSIL		EQU	000Fh
VIDAS			EQU	0003h
MASK_ALEATORIA		EQU	8016h
ZERO			EQU	0000h
UM			EQU	0001h
MAX_ALEATORIO		EQU	004Eh
MIN_VALOR		EQU	000Ah
MAX_VALOR		EQU	001Eh
LINHA0_LCD		EQU	8000h
LINHA1_LCD		EQU	8010h
COMECO_PONT		EQU	8008h
COMECO_PONTMAX		EQU	8018h
FIM_PONT		EQU	800Bh
FIM_PONTMAX		EQU	801Bh
COMECO_VIDAS		EQU	800Eh
MOVIMENTO		EQU	0002h
LED			EQU	0003h


;------------------------------------------------------------------------------
; 	ZONA II: definicao de variaveis

			ORIG 	8000h
VarTexto1 		STR 	'Bem vindo a chuva de meteoros', FIM_TEXTO
VarTexto2 		STR 	'Prima o interruptor I1 para comecar', FIM_TEXTO
Terra	 		STR '--------------------------------------------------------------------------------', FIM_TEXTO
Meteoro 		STR 	'*' , FIM_TEXTO
Canhao 			STR 	'<^>' , FIM_TEXTO
Missil 			STR 	'|' , FIM_TEXTO
VarTexto3 		STR 	'Fim do jogo', FIM_TEXTO
VarTexto4 		STR 	'Prima o interruptor I1 para recomecar', FIM_TEXTO
Dummy			STR	' ', FIM_TEXTO
LCDL1			STR	'PONTOS: 0000 *0', FIM_TEXTO
LCDL2			STR	'MAX: 0000', FIM_TEXTO
Pos_canhao		WORD	PONT_INICIAL
Menu			WORD	ZERO
PodeDisparar		WORD	ZERO
HaMissil		WORD	ZERO
Pos_meteoro		WORD	ZERO
Pos_missil		WORD	ZERO
Contador_missil		WORD	CONTADOR_MISSIL
Canhao_moveu		WORD	UM
Vidas			WORD	VIDAS
Pontuacao		WORD	ZERO
PontuacaoMax		WORD	ZERO
Valor_Aleatorio		WORD	UM
Pontos_Aleatorio	WORD	ZERO
Mov_Esq			WORD	ZERO
Mov_Dir			WORD	ZERO
Leds_acesos		WORD	ZERO
Acende_LED		WORD	LED
Move_meteoro		WORD	MOVIMENTO

;	Zona III: Posicionar as máscaras.
			ORIG	FE00h
INT0			WORD	CanhaoEsq
INT1			WORD	SaiMenu
INT2			WORD	AtivaMissil
			ORIG	FE0Bh
INTB			WORD	CanhaoDir
			ORIG	FE0Fh
INTF			WORD	TimerSub

;	Zona IV: Código
;		Funcao de cada registo:
;			- R1 serve de intermedio entre trocas de variaveis.
;			- R2 serve de apontador para strings.
;			- R3 serve para guardar a posicao onde o caracter vai ser escrito.
;			- R5 serve para guardar a mascara para gerar valores aleatorios.
;			- R7 serve para inicializar o timer, mascaras e stack.

;		IV.1 - Inicio

		ORIG	0000h
		JMP	Inicio

;		IV.2 - Rotinas de tratamento a interrupcoes.

;  SaiMenu: Rotina que ativa a variável que deixa o utilizador passar o menu inicial ou reiniciar o jogo.

SaiMenu:	INC	M[Menu]
		RTI

;  AtivaMissil: Rotina que altera a posicao do missil para a primeira em que este e registado.

AtivaMissil:	CMP 	M[PodeDisparar], R0
		BR.Z	SaiAtivaMiss
		MOV	M[Leds_acesos], R0
		MOV	R1, M[Pos_canhao]
		INC	R1
		SUB	R1, LINHA
		MOV	M[Pos_missil], R1
		DEC	M[PodeDisparar]
SaiAtivaMiss:	RTI

;  CanhaoDir: Rotina que modifica a posicao do inicio do canhao, incrementando uma posicao.

CanhaoDir:	MOV	R1, M[Pos_canhao]
		CMP	R1, MAX_DIR
		BR.Z	FimDir
		INC	M[Pos_canhao]
		INC	M[Canhao_moveu]
FimDir:		RTI

;  CanhaoEsq: Rotina que modifica a posicao do inicio do canhao, decrementando uma posicao.

CanhaoEsq:	MOV	R1, M[Pos_canhao]
		CMP	R1, MAX_ESQ
		BR.Z	FimEsq
		DEC	M[Pos_canhao]
		INC	M[Canhao_moveu]
FimEsq:		RTI

;  TimerSub: Rotina que atualiza todas as posicoes de misseis e meteoros e a quantidade de LEDs acesos

TimerSub:	DEC	M[Move_meteoro]
		DEC	M[Acende_LED]
		CMP	M[Move_meteoro], R0
		BR.NZ	Next
		MOV	R1, M[Pos_meteoro]
		ADD	R1, LINHA
		MOV	M[Pos_meteoro], R1
		MOV	R1, M[Pos_missil]
		SUB	R1, LINHA
		MOV	M[Pos_missil], R1
		MOV	R1, MOVIMENTO
		MOV	M[Move_meteoro], R1
Next:		CMP	M[Acende_LED], R0
		BR.NZ	Next1
		MOV	R1, M[Leds_acesos]
		STC
		ROLC	R1, 1
		MOV	R1, LED
		MOV	M[Move_meteoro], R1
Next1:		MOV	R1, TEMPO
		MOV 	M[TIMER_VALUE], R1
		MOV 	R1, ENABLE_TIMER
		MOV	M[TIMER_CONTROL], R1
		RTI

; EscEcra: Rotina que escreve no ecra a string que recebe na posicao que recebe:

EscEcra:	MOV	R6, M[R2]
		CMP	R6, FIM_TEXTO
		BR.Z	FimString
		I2OP	R6, R3
		INC	R2
		INC	R3
		BR	EscEcra
FimString:	RET

; Conversor: Rotina que converte o conteudo na posicao de memoria e retorna-o em decimal.

Conversor:	MOV	R2, 000Ah
		DIV	R1, R2
		SHL	R1, 4
		ADD	R1, R2
		CMP	R1, 00A0h
		BR.N	NextConvert
		MOV	R3, R1
		AND	R3, 000Fh
		SHR	R1, 4
		MOV	R2, 000Ah
		DIV	R1, R2
		SHL	R1, 8
		SHL	R2, 4
		ADD	R1, R2
		ADD	R1, R3
NextConvert:	CMP	R1, 0A00h
		BR.N	MiddleConvert
		MOV	R3, R1
		AND	R3, 00FFh
		SHR	R1, 8
		MOV	R2, 000Ah
		DIV	R1, R2
		SHL	R1, 12
		SHL	R2, 8
		ADD	R1, R2
		ADD	R1, R3
MiddleConvert:	CMP	R1, A000h
		BR.N	FimConvert
		MOV	R3, R1
		AND	R3, 00ffh
		MOV	R1, R3
FimConvert:	RET

; GeraAleatorio: Rotina que gera um valor aleatorio entre 0000h e 004Fh, guardando-o em R4.

GeraAleatorio:	MOV	R6, UM
		MOV	R5, MASK_ALEATORIA
		MOV	R4, M[Valor_Aleatorio]
		AND	R4, R6
		BR.NZ	ElseAlea
		MOV	R4, M[Valor_Aleatorio]
		ROR	R4, UM
		BR	SaiAlea
ElseAlea:	MOV	R4, M[Valor_Aleatorio]
		XOR	R4, R5
		ROR	R4, UM
SaiAlea:	AND	R4, 00FFh
		CMP	R4, MAX_ALEATORIO
		BR.P	GeraAleatorio
		MOV	M[Valor_Aleatorio], R4
		RET

; GeraPontucao: Rotina que gera um valor aleatorio entre 10 e 49, serve para a pontuacao.

GeraPontuacao:	MOV	R6, UM
		MOV	R5, MASK_ALEATORIA
		MOV	R4, M[Pontos_Aleatorio]
		AND	R4, R6
		BR.NZ	ElsePont
		MOV	R4, M[Pontos_Aleatorio]
		ROR	R4, UM
		BR	SaiPont
ElsePont:	MOV	R4, M[Pontos_Aleatorio]
		XOR	R4, R5
		ROR	R4, UM
SaiPont:	AND	R4, 00FFh
		CMP	R4, MIN_VALOR
		BR.N	GeraPontuacao
		CMP	R4, MAX_VALOR
		BR.P	GeraPontuacao
		MOV	M[Pontos_Aleatorio], R4
		RET

; VerificaChoque: Rotina que verifica se o meteoro choca contra a Terra ou contra um missil e se o missil choca no teto.

VerificaChoque:	MOV	R1, M[Pos_meteoro]
		ADD	R1, LINHA
		MOV	R2, M[Pos_missil]
		CMP	R1, R2
		BR.NZ	DestroiAmbos
		ADD	R1, LINHA
		CMP	R1, R2
		BR.NZ	DestroiAmbos
		BR	LimiteMeteoro
DestroiAmbos:	DEC	M[HaMissil]		; se ambos chocarem, atualiza posicao do missil, desliga o enable do missil e gera uma nova pontuacao com o valor do meteoro
		CALL	LimpaMissilL
		CALL	LimpaMeteoroL
		MOV	R1, M[Valor_Aleatorio]
		CALL	GeraAleatorio
		MOV	M[Pos_meteoro], R1
		MOV	R1, M[Pontos_Aleatorio]
		CALL	GeraPontuacao
		ADD	M[Pontuacao], R1	
		BR	Fim_Verificar
LimiteMeteoro:	MOV	R1, M[Pos_meteoro]	; verifica se o meteoro bate na terra e, se bater, altera a sua posicao e decrementa o numero de vidas
		ADD	R1, LINHA
		MOV	R2, TERRA
		AND	R1, FF00h
		CMP	R1, R2
		BR.NZ	LimiteMissil
		MOV	R1, M[Valor_Aleatorio]
		CALL	GeraAleatorio
		MOV	M[Pos_meteoro], R1
		DEC	M[Vidas]
LimiteMissil:	CMP	M[HaMissil], R0	; verifica se o missil chega ao teto de jogo, se chegar, desliga o enable
		BR.Z	Fim_Verificar
		MOV	R1, M[Pos_missil]
		SUB	R1, LINHA
		AND	R1, FF00h
		BR.NZ	Fim_Verificar
		DEC	M[HaMissil]
Fim_Verificar:	RET

; AtualPont: Rotina que atualiza todos os outputs que demonstram a pontuacao.


AtualPont:	CALL	AtualizaLCDs
		CALL	AtualizaSegms
		CALL	AtualizaLEDs
		RET

AtualizaLEDs:	MOV	R6, M[Leds_acesos]
		MOV	M[IO_LEDS], R6
		RET

AtualizaSegms:	MOV	R1, M[Pontuacao]
		CALL	Conversor
		MOV	R2, R1
		AND	R2, F000h
		MOV	M[IO_DISPLAY_0], R2
		MOV	R2, R1
		AND	R2, 0F00h
		MOV	M[IO_DISPLAY_1], R2
		MOV	R2, R1
		AND	R2, 00F0h
		MOV	M[IO_DISPLAY_2], R2
		MOV	R2, R1
		AND	R2, 000Fh
		MOV	M[IO_DISPLAY_3], R2
		RET

Inicia_LCDs:	MOV	R1, M[Pontuacao]
		CALL	Conversor
		MOV	R5, FIM_TEXTO
		MOV	R2, LCDL1
		MOV	R3, LINHA0_LCD
Escreve0:	MOV	R4, M[R2]
		MOV	M[IO_LCD_CONTROL], R3
		MOV	M[IO_LCD_WRITE], R4
		INC	R2
		INC	R3
		CMP	M[R2], R5
		BR.NZ	Escreve0
		MOV	R2, LCDL2
		MOV	R3, LINHA1_LCD
Escreve1:	MOV	R4, M[R2]
		MOV	M[IO_LCD_CONTROL], R3
		MOV	M[IO_LCD_WRITE], R4
		INC	R2
		INC	R3
		CMP	M[R2], R5
		BR.NZ	Escreve1
		RET

AtualizaLCDs:	MOV	R1, M[Pontuacao]
		CALL	Conversor
		MOV	R2, COMECO_PONT
CicloAtlPLCD:	MOV	R3, R1
		AND	R3, F000h
		ADD	R3, 0030h
		MOV	M[IO_LCD_CONTROL], R2
		MOV	M[IO_LCD_WRITE], R3
		SHR	R1, 0004h
		INC	R2
		CMP	R2, FIM_PONT
		BR.NZ	CicloAtlPLCD
		RET

AtlVidasLCD:	MOV	R2, COMECO_VIDAS
		MOV	R1, 0003h
		SUB	R1, M[Vidas]
		ADD	R1, 0030h
		MOV	M[IO_LCD_CONTROL], R2
		MOV	M[IO_LCD_WRITE], R1
		RET

AtualPontMax:	MOV	R1, M[PontuacaoMax]
		CALL	Conversor
		MOV	R2, COMECO_PONTMAX
CicloAtlPMAX:	MOV	R3, R1
		AND	R3, F000h
		ADD	R3, 0030h
		MOV	M[IO_LCD_CONTROL], R2
		MOV	M[IO_LCD_WRITE], R3
		SHR	R1, 0004h
		INC	R2
		CMP	R2, FIM_PONTMAX
		BR.NZ	CicloAtlPMAX
		RET

; DesMenu: Rotina que escreve na janela o menu inicial.

DesMenu:	DSI
		MOV	R2, VarTexto1
		MOV	R3, TEXTO1
		CALL	EscEcra
		MOV	R2, VarTexto2
		MOV	R3, TEXTO2
		CALL	EscEcra
		ENI
		RET

; DesFim: Rotina que escreve na janela o menu final.

DesFim:		DSI
		MOV	R2, VarTexto3
		MOV	R3, TEXTO1
		CALL	EscEcra
		MOV	R2, VarTexto4
		MOV	R3, TEXTO2
		CALL	EscEcra
		ENI
		RET

; DesTerra: Rotina que desenha a terra na janela de jogo.

DesTerra:	DSI
		MOV	R2, Terra
		MOV	R3, TERRA
		CALL	EscEcra
		ENI
		RET

; DesCanhao: Rotina que desenha o canhao na janela de jogo.

DesCanhao:	DSI
		CMP	M[Canhao_moveu], R0
		BR.Z	Canhao_n_moveu
		DEC	M[Canhao_moveu]
		CALL	LimpaCanhao
		MOV	R2, Canhao
		MOV	R3, M[Pos_canhao]
		CALL	EscEcra
Canhao_n_moveu:	ENI
		RET
	
; DesMeteoro: Rotina que desenha o meteoro no jogo.

DesMeteoro:	DSI
		CALL	LimpaMeteoro
		MOV	R2, Meteoro
		MOV	R3, M[Pos_meteoro]
		CALL	EscEcra
		ENI
		RET

; DesMissil: Rotina que desenha o missil no jogo.

DesMissil:	CMP	M[HaMissil], R0
		BR.Z	FimDesMissil
		DSI
		CALL	LimpaMissil
		MOV	R2, Missil
		MOV	R3, M[Pos_missil]
		CALL	EscEcra
		ENI
FimDesMissil:	RET


; LimpaCanhao: Rotina que limpa o canhao da janela de texto.

LimpaCanhao:	DSI
		MOV	R1, TAM_CANHAO
		MOV	R3, M[Pos_canhao]
CicLimCanhao:	MOV	R2, Dummy
		CALL	EscEcra
		INC	R3
		DEC	R1
		BR.NZ	CicLimCanhao
		ENI
		RET		

; LimpaJanela:  Rotina que limpa a janela de texto do simulador.

LimpaJanela:   	MOV     R1, M[Dummy]
		MOV	R2, 0001h
LimpaLinha:	I2OP	R1, R2
		INC	R2
		MOV	R3, R2
		AND	R3, 00FFh
		CMP	R3, 004fh
		BR.NZ	LimpaLinha
		AND	R2, FF01h
		ADD	R2, LINHA
		CMP	R4, 174Fh
		BR.NZ	LimpaLinha
                RET


; LimpaMissil: Rotina que escreve o missil no mapa

LimpaMissil:	CMP	M[HaMissil], R0
		BR.Z	FimLimMissil
		DSI
		MOV	R2, Dummy
		MOV	R3, M[Pos_missil]
		ADD	R3, LINHA
		CALL	EscEcra
		ENI
FimLimMissil:	RET

; LimpaMeteoro: Rotina que escreve o meteoro no mapa


LimpaMeteoro:	DSI
		MOV	R2, Dummy
		MOV	R3, M[Pos_missil]
		SUB	R3, LINHA
		CALL	EscEcra
		ENI
		RET

; LimpaMissilL: Rotina que limpa o missil na posicao em que se encontra.

LimpaMissilL:	DSI
		MOV	R2, Dummy
		MOV	R3, M[Pos_missil]
		CALL	EscEcra
		ENI
		RET

; LimpaMeteoroL: Rotina que limpa o meteoro na posicao em que se encontra.

LimpaMeteoroL:	DSI
		MOV	R2, Dummy
		MOV	R3, M[Pos_meteoro]
		CALL	EscEcra
		ENI
		RET


;		V - Programa Principal.

Inicio:		MOV	R7, SP_INICIAL
		MOV	SP, R7
		MOV	R7, INT_MASK
		MOV	M[INT_MASK_ADDR], R7
		MOV	R7, FFFFh
		MOV	M[IO_LEDS], R7
		CALL	Inicia_LCDs
		CALL	DesMenu
		ENI
Menu1:		CMP	M[Menu], R0
		BR.Z	Menu1
		CALL	LimpaJanela
Recomeca:	DEC	M[Menu]
		MOV	M[Pontuacao], R0
		MOV	R1, TEMPO
		MOV 	M[TIMER_VALUE], R1
		MOV 	R1, ENABLE_TIMER
		MOV	M[TIMER_CONTROL], R1
		CALL	DesTerra
		CALL	GeraAleatorio
		MOV	R1, M[Valor_Aleatorio]
		MOV	M[Pos_meteoro], R1
Meio:		CALL	DesCanhao
		CALL	VerificaChoque
		CALL	DesMissil
		CALL	DesMeteoro
		CALL	AtualPont
		CMP	M[Vidas], R0
		BR.Z	Fim
		BR	Meio
Fim:		CALL	LimpaJanela
		CALL	DesFim
		MOV	R1, M[Pontuacao]
		CMP	M[PontuacaoMax], R1
		BR.NN	Wait
		MOV	M[PontuacaoMax], R1
		CALL	AtualPontMax
Wait:		CMP	M[Menu], R0
		BR.Z	Wait
		JMP	Recomeca
