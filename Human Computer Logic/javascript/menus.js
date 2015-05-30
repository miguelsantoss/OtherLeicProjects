/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                                ///
///                                           Mudar posição nos menus                                              ///
///                                                                                                                ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/
var onMenu = 1;
var button = 1;
var menu_actual = "carousel_modelo_carro";
var maxLimit = 9;
var minLimit = 0;
var selected = "#" + button.toString();
var opcoes_carrocel = new Array();
var menu_anterior = "n";
var ajuda_activa = 0;

opcoes_carrocel[0] = "Personalizar";
opcoes_carrocel[1] = "Combustível";
opcoes_carrocel[2] = "Paquímetro";
opcoes_carrocel[3] = "GPS";
opcoes_carrocel[4] = "Ar Condicionado";
opcoes_carrocel[5] = "Câmera traseira";
opcoes_carrocel[6] = "Estado do Motor";
opcoes_carrocel[7] = "Leitor de DVD";
opcoes_carrocel[8] = "Rádio";
opcoes_carrocel[9] = "Activar Ajuda";
opcoes_carrocel[13] = "Marca Favorita";
opcoes_carrocel[14] = "Configurar Alerta";
opcoes_carrocel[15] = "Bombas Mais Próximas";
opcoes_carrocel[16] = "Activar Ajuda";
opcoes_carrocel[20] = "Pequeno";
opcoes_carrocel[21] = "Médio";
opcoes_carrocel[22] = "Grande";
opcoes_carrocel[23] = "Activar Ajuda";
opcoes_carrocel[46] = "Favorita";
opcoes_carrocel[47] = "Mais Barata";
opcoes_carrocel[48] = "Mais Perto";
opcoes_carrocel[49] = "Activar Ajuda";
opcoes_carrocel[63] = "Pagar com Dinheiro";
opcoes_carrocel[64] = "Débito Direto";
opcoes_carrocel[65] = "CTT";
opcoes_carrocel[66] = "Activar Ajuda";
opcoes_carrocel[87] = "Bagageira";
opcoes_carrocel[88] = "Bancos";
opcoes_carrocel[89] = "Activar Ajuda";

var legenda_carrocel = new Array();
legenda_carrocel[0] = "   Entrar              Desligar o sistema";
legenda_carrocel[1] = "   Entrar              Desligar o sistema";
legenda_carrocel[2] = "   Entrar              Desligar o sistema";
legenda_carrocel[3] = "   Desligar o sistema";
legenda_carrocel[4] = "   Desligar o sistema";
legenda_carrocel[5] = "   Desligar o sistema";
legenda_carrocel[6] = "   Desligar o sistema";
legenda_carrocel[7] = "   Desligar o sistema";
legenda_carrocel[8] = "   Desligar o sistema";
legenda_carrocel[9] = "   Activar            Desligar o sistema";
legenda_carrocel[13] = "  Editar              Voltar atrás";
legenda_carrocel[14] = "  Editar              Voltar atrás";
legenda_carrocel[15] = "  Editar              Voltar atrás";
legenda_carrocel[16] = "  Activar            Voltar atrás";
legenda_carrocel[20] = "    Activar/Editar              Voltar atrás";
legenda_carrocel[21] = "    Activar/Editar              Voltar atrás";
legenda_carrocel[22] = "    Activar/Editar              Voltar atrás";
legenda_carrocel[23] = "    Activar              Voltar atrás";
legenda_carrocel[46] = "  Mostrar Bombas                Sair";
legenda_carrocel[47] = "  Mostrar Bombas                Sair";
legenda_carrocel[48] = "  Mostrar Bombas                Sair";
legenda_carrocel[49] = "  Activar                Sair";
legenda_carrocel[63] = "   Pagar              Voltar atrás";
legenda_carrocel[64] = "   Pagar              Voltar atrás";
legenda_carrocel[65] = "   Pagar              Voltar atrás";
legenda_carrocel[66] = "   Activar            Voltar atrás";
legenda_carrocel[87] = "   Editar             Voltar atrás";
legenda_carrocel[88] = "   Editar             Voltar atrás";
legenda_carrocel[89] = "   Activar           Voltar atrás";

var ajudas_menu = new Array();
ajudas_menu[0] = "<br>    <u>Personalizacão</u>:<br>    Permite a personalização<br>    do estado actual do carro<br>    Activando um modelo, ou <br>    alterando as suas<br>    características";
ajudas_menu[1] = "<br>    <u>Configurar Alerta</u>:<br>    Definir o alerta de <br>    autonomia restante (Km).<br>    <u>Bombas Mais Próximas</u>:<br>    Mapa com os postos mais<br>    próximos.<br>    <u>Marca Favorita</u>:<br>    Definir qual a gasolineira<br>    favorita.";
ajudas_menu[2] = "<br>    <u>Paquímetro</u>:<br>    Iniciar a contagem<br>    quando estaciona numa<br>    área paga<br><br><br>    <i>Este aviso aparece<br>    automaticamente, com a<br>    possibilidade de ser<br>    ignorado.</i>";
ajudas_menu[3] = "<br>    <u>GPS</u>:<br>    Consulta de informações<br>    relacionadas com a<br>    localização, e pontos<br>    de interesse.<br><br><br><br>    <i>Funcionalidade não<br>    implementada.</i>";
ajudas_menu[4] = "<br>    <u>Ar Condicionado</u>:<br>    Permite controlar o fluxo<br>    de ar e a temperatura<br>    dentro do carro.<br><br><br><br><br>    <i>Funcionalidade não<br>    implementada.<i>";
ajudas_menu[5] = "<br>    <u>Câmera Traseira</u>:<br>    Permite a visualização<br>    dos pontos mortos e<br>    dos bancos traseiros.<br><br><br><br><br>    <i>Funcionalidade não<br>    implementada.<i>";
ajudas_menu[6] = "<br>    <u>Estado do Motor</u>:<br>    Controlo do estado do<br>    motor.<br><br><br><br><br><br>    <i>Funcionalidade não<br>    implementada.<i>";
ajudas_menu[7] = "<br>    <u>Leitor de DVD</u>:<br>    Reprodução do conteúdo<br>    do DVD inserido.<br><br><br><br><br><br>    <i>Funcionalidade não<br>    implementada.<i>";
ajudas_menu[8] = "<br>    <u>Rádio</u>:<br>    Reprodução de música<br>    através da rádio, ou de<br>    um CD introduzido<br><br><br><br><br>    <i>Funcionalidade não<br>    implementada.<i>";
ajudas_menu[9] = "<br>    <u>Activar Ajuda</u>:<br>    Activa ou Desactiva a<br>    ajuda sobre as opções.";
ajudas_menu[13] = "<br>    <u>Marca Favorita</u>:<br>    Definir qual a nossa<br>    marca (gasolineira)<br>    favorita, para seleção,<br>    quando é atingido o<br>    alerta de combustível."
ajudas_menu[14] = "<br>    <u>Configurar Alerta</u>:<br>    Definir a quantos Km<br>    pretende ser notificado<br>    para a autonomia de<br>    combustível restante.";
ajudas_menu[15] = "<br>    <u>Bombas mais próximas</u>:<br>    Mostra um mapa com as<br>    bombas mais próximas da<br>    sua localização actual";
ajudas_menu[16] = "<br>    <u>Activar Ajuda</u>:<br>    Activa ou Desactiva a<br>    ajuda sobre as opções.";
ajudas_menu[20] = "<br>    <u>Pequeno</u>:<br>    Activar ou personalizar<br>    o modelo pequeno.";
ajudas_menu[21] = "<br>    <u>Médio</u>:<br>    Activar ou personalizar<br>    o modelo médio.";
ajudas_menu[22] = "<br>    <u>Grande</u>:<br>    Activar ou personalizar<br>    o modelo grande.";
ajudas_menu[23] = "<br>    <u>Activar Ajuda</u>:<br>    Activa ou Desactiva a<br>    ajuda sobre as opções.";
ajudas_menu[26] = "<br>    <u>Iniciar</u>:<br>    Inicia a contagem de<br>    tempo na área paga.";
ajudas_menu[27] = "<br>    <u>Ignorar</u>:<br>    Ignora o aviso e volta<br>    ao menu inicial.";
ajudas_menu[40] = "<br>    <u>Sim</u>:<br>    Mostra como escolher a<br>    bomba onde reabastecer.";
ajudas_menu[41] = "<br>    <u>Não</u>:<br>    Ignora o aviso de<br>    combustível baixo.";
ajudas_menu[46] = "<br>    <u>Favorita</u>:<br>    Mostra as bombas mais<br>    próximas da gasolineira<br>    escolhida como favorita.<br><br><br><br><br>    <i>As bombas apresentadas<br>    encontram-se dentro da<br>    autonomia restante</i>";
ajudas_menu[47] = "<br>    <u>Mais Barata</u>:<br>    Mostra as bombas mais<br>    baratas na região.<br><br><br><br><br><br>    <i>As bombas apresentadas<br>    encontram-se dentro da<br>    autonomia restante</i>";
ajudas_menu[48] = "<br>    <u>Mais Perto</u>:<br>    Mostra as bombas mais<br>    perto na região.<br><br><br><br><br><br>    <i>As bombas apresentadas<br>    encontram-se dentro da<br>    autonomia restante</i>";
ajudas_menu[49] = "<br>    <u>Activar Ajuda</u>:<br>    Activa ou Desactiva a<br>    ajuda sobre as opções.";
ajudas_menu[53] = "<br>    <u>Sim</u>:<br>    Ignorar o aviso.";
ajudas_menu[54] = "<br>    <u>Não</u>:<br>    Não ignorar o aviso.";
ajudas_menu[57] = "<br>    <u>Sim</u>:<br>    Ignorar o aviso.";
ajudas_menu[58] = "<br>    <u>Não</u>:<br>    Não ignorar o aviso.";
ajudas_menu[60] = "<br>    <u>Parar a Contagem</u>:<br>    Parar a contagem e<br>    proceder para o pagamento.";
ajudas_menu[63] = "<br>    <u>Pagar com Dinheiro</u>:<br>    Pagar através do<br>    paquímetro mais próximo.";
ajudas_menu[64] = "<br>    <u>Débito Direto</u>:<br>    Pagar através de desconto<br>    directo na conta.";
ajudas_menu[65] = "<br>    <u>CTT</u>:<br>    Pagar através dos CTT.";
ajudas_menu[66] = "<br>    <u>Activar Ajuda</u>:<br>    Activa ou Desactiva a<br>    ajuda sobre as opções.";
ajudas_menu[68] = "<br>    <u>Sim</u>:<br>    Continuar a contagem do<br>    tempo.";
ajudas_menu[69] = "<br>    <u>Não</u>:<br>    Não Continuar a contagem<br>    do tempo, e prroceder para<br>    o pagamento.";
ajudas_menu[71] = "<br>    <u>Confirmar</u>:<br>    Confirma o pagamento<br>    através de Débito.";
ajudas_menu[72] = "<br>    <u>Cancelar</u>:<br>    Cancela e volta ao menu<br>    anterior.";
ajudas_menu[75] = "<br>    <u>Confirmar</u>:<br>    Confirma o pagamento<br>    com dinheiro.";
ajudas_menu[76] = "<br>    <u>Cancelar</u>:<br>    Cancela e volta ao menu<br>    anterior.";
ajudas_menu[77] = "<br>    <u>Paquímetro</u>:<br>    Mapa com a localização<br>    do paquímetro mais<br>    próximo.";
ajudas_menu[79] = "<br>    <u>Confirmar</u>:<br>    Confirma o pagamento<br>    através dos CTT";
ajudas_menu[80] = "<br>    <u>Cancelar</u>:<br>    Cancela e volta ao menu<br>    anterior.";
ajudas_menu[82] = "<br>    <u>Activar</u>:<br>    Activa o modelo,<br>    aplicando as alterações<br>    definidas ao carro.";
ajudas_menu[83] = "<br>    <u>Editar</u>:<br>    Edita o modelo,<br>    podendo alterar as<br>    características do carro.";
ajudas_menu[84] = "<br>    <u>Voltar</u>:<br>    Voltar ao menu anterior.";
ajudas_menu[87] = "<br>    <u>Bagageira</u>:<br>    Altera o tamanho da<br>    bagageira do modelo.";
ajudas_menu[88] = "<br>    <u>Bancos</u>:<br>    Altera o número de bancos.";
ajudas_menu[89] = "<br>    <u>Activar Ajuda</u>:<br>    Activa ou Desactiva a<br>    ajuda sobre as opções.";
ajudas_menu[92] = "<br>    <u>Tamanho</u>:<br>    Activa ou Desactiva a<br>    ajuda sobre as opções.";
ajudas_menu[93] = "<br>    <u>Activar Ajuda</u>:<br>    Activa ou Desactiva a<br>    ajuda sobre as opções.";
ajudas_menu[92] = "<br>    <u>Bancos</u>:<br>    Permite alterar quantos<br>    estão disponíveis no carro.";
ajudas_menu[93] = "<br>    <u>Concluir</u>:<br>    Voltar ao menu anterior.";
ajudas_menu[98] = "<br>    <u>Concluir</u>:<br>    Voltar ao menu anterior.";


var legendas_alvo = new Array();
legendas_alvo[26] = "legenda_paquimetro_pop_up";
legendas_alvo[27] = "legenda_paquimetro_pop_up";
legendas_alvo[30] = "legenda_configurar_combustivel_marcas";
legendas_alvo[31] = "legenda_configurar_combustivel_marcas";
legendas_alvo[35] = "legenda_configurar_combustivel_km";
legendas_alvo[36] = "legenda_configurar_combustivel_km";
legendas_alvo[40] = "legenda_combustivel_pop_up";
legendas_alvo[41] = "legenda_combustivel_pop_up";
legendas_alvo[53] = "legenda_combustivel_pop_up_ignora";
legendas_alvo[54] = "legenda_combustivel_pop_up_ignora";
legendas_alvo[57] = "legenda_paquimetro_pop_up_ignora";
legendas_alvo[58] = "legenda_paquimetro_pop_up_ignora";
legendas_alvo[68] = "legenda_paquimetro_continuar_a_contar";
legendas_alvo[69] = "legenda_paquimetro_continuar_a_contar";
legendas_alvo[75] = "legenda_paquimetro_metodo_pagamento_dinheiro";
legendas_alvo[76] = "legenda_paquimetro_metodo_pagamento_dinheiro";
legendas_alvo[82] = "legenda_personalizar_geral_activar_editar";
legendas_alvo[83] = "legenda_personalizar_geral_activar_editar";
legendas_alvo[84] = "legenda_personalizar_geral_activar_editar";
legendas_alvo[92] = "legenda_editar_bancos";
legendas_alvo[93] = "legenda_editar_bancos";
legendas_alvo[97] = "legenda_editar_bagagem";
legendas_alvo[98] = "legenda_editar_bagagem";

var legendas_a_por = new Array();
legendas_a_por[26] = "   Iniciar                     Ignorar";
legendas_a_por[27] = "   Ignorar                    Ignorar";
legendas_a_por[30] = "   Editar marca favorita             Voltar atrás";
legendas_a_por[31] = "   Voltar atrás                            Voltar atrás";
legendas_a_por[35] = "   Editar Km para o alerta           Voltar atrás";
legendas_a_por[36] = "   Voltar atrás                             Voltar atrás";
legendas_a_por[40] = "   Sim                        Voltar atrás";
legendas_a_por[41] = "   Não                        Voltar atrás";
legendas_a_por[53] = "   Sim                        Voltar atrás";
legendas_a_por[54] = "   Não                        Voltar atrás";
legendas_a_por[57] = "   Sim                        Voltar atrás";
legendas_a_por[58] = "   Não                        Voltar atrás";
legendas_a_por[68] = "   Sim                        Voltar atrás";
legendas_a_por[69] = "   Não                        Voltar atrás";
legendas_a_por[75] = "   Confirmar               Voltar atrás";
legendas_a_por[76] = "   Cancelar                Voltar atrás";
legendas_a_por[82] = "    Activar                           Voltar atrás";
legendas_a_por[83] = "    Editar                             Voltar atrás";
legendas_a_por[84] = "    Voltar                             Voltar atrás";
legendas_a_por[92] = "   Editar número                           Voltar Atrás";
legendas_a_por[93] = "   Voltar atrás                               Voltar Atrás";
legendas_a_por[97] = "   Editar Tamanho                    Voltar Atrás";
legendas_a_por[98] = "   Voltar atrás                            Voltar Atrás";

var carrocel_class = new Array();
carrocel_class[0] = "item_left";
carrocel_class[1] = "item_mid";
carrocel_class[2] = "item_right";
carrocel_class[3] = "hidden";

var bombas_favoritas = new Array();
bombas_favoritas[0] = "images/bombas/icon_galp.png";
bombas_favoritas[1] = "images/bombas/icon_bp.png";
bombas_favoritas[2] = "images/bombas/icon_repsol.png";
bombas_favoritas[3] = "images/bombas/icon_cepsa.png";
bombas_favoritas[4] = "images/bombas/icon_jumbo.png";
bombas_favoritas[5] = "images/bombas/icon_total.png";
bombas_favoritas[6] = "images/bombas/icon_shell.png";

function ActivarAjuda() {
	if (ajuda_activa === 0) {
		$('.menus').css('background-image', 'url(images/ajuda1.png)');
		$('#ajuda_menus').show(0);
		ajuda_activa = 1;
		actualizar_ajuda();
	}
	else {
		$('.menus').css('background-image', 'url(images/2.png)');
		$('#ajuda_menus').hide(0);
		ajuda_activa = 0;
	}
}

function actualizar_ajuda() {
	document.getElementById("span_ajuda").innerHTML = ajudas_menu[button];
	if (onMenu === 6) {
		document.getElementById("span_ajuda").innerHTML = ajudas_menu[97];
	}
}

$(document).jkey('a, s',function(key){
	if (onMenu === 1) {
		var toEliminate = 0;
		var toAppear = 0;
		var goingToMiddle = 0;
		if(key == 'a'){
			toEliminate = button+1;
			toAppear = button-2;
			goingToMiddle = button-1;
			if (toEliminate > maxLimit) {
				toEliminate = minLimit;
			}
			if (toAppear < minLimit - 1) {
				toAppear = maxLimit - 1;
			}
			if (toAppear < minLimit) {
				toAppear = maxLimit;
			}
			if (goingToMiddle < minLimit) {
				goingToMiddle = maxLimit;
			}
			change_pos_left(button.toString(), toEliminate.toString(), goingToMiddle.toString(), toAppear.toString());
			button--;
			if (button < minLimit) {
				button = maxLimit;
			}
			selected = "#" + button.toString();
		}
		else{
			toEliminate = button-1;
			toAppear = button+2;
			goingToMiddle = button+1;
			if (toEliminate < minLimit) {
				toEliminate = maxLimit;
			}
			if (toAppear > maxLimit + 1) {
				toAppear = minLimit + 1;
			}
			if (toAppear > maxLimit) {
				toAppear = minLimit;
			}
			if (goingToMiddle > maxLimit) {
				goingToMiddle = minLimit;
			}
			change_pos_right(button.toString(), toEliminate.toString(), goingToMiddle.toString(), toAppear.toString());
			button++;
			if (button > maxLimit) {
				button = minLimit;
			}
			selected = "#" + button.toString();
			
		}
		actualizar_ajuda();
	}
	else if(onMenu === 2) {
		if(key == 'a'){
			deselect(button.toString());
			button--;
			if (button < minLimit){
				button = maxLimit;
			}
		actualizar_ajuda();
		selected = "#" + button.toString();
		select(button.toString());
		document.getElementById(legendas_alvo[button]).firstChild.innerHTML = legendas_a_por[button];
		}
		else{
		deselect(button.toString());
		button++;
			if (button > maxLimit){
				button = minLimit;
			}
		actualizar_ajuda();
		selected = "#" + button.toString();
		select(button.toString());
		document.getElementById(legendas_alvo[button]).firstChild.innerHTML = legendas_a_por[button];
		}
		
	}
	else if (onMenu === 3) {
		if(key == 'a'){
			button--;
			removeClass(document.getElementById("seta_direita"), "hidden");
			if (button <= minLimit){
				button = minLimit;
				document.getElementById("seta_esquerda").className = "hidden";
			}
			document.getElementById("30").firstChild.innerHTML = possiveis_favoritos[button];
			document.getElementById("image_combustivel").firstChild.src = bombas_favoritas[button];
		}
		else{
			button++;
			removeClass(document.getElementById("seta_esquerda"), "hidden");
			if (button >= maxLimit){
				button = maxLimit;
				document.getElementById("seta_direita").className = "hidden";
			}
			document.getElementById("30").firstChild.innerHTML = possiveis_favoritos[button];
			document.getElementById("image_combustivel").firstChild.src = bombas_favoritas[button];
		}
	}
	else if (onMenu === 4) {
		if(key == 'a'){
			button-=5;
			removeClass(document.getElementById("seta_direita_2"), "hidden");
			if (button <= minLimit){
				button = minLimit;
				document.getElementById("seta_esquerda_2").className = "hidden";
			}
			if (button === 0) {
				document.getElementById("35").firstChild.innerHTML = "Desligado";
			}
			else {
				document.getElementById("35").firstChild.innerHTML = button.toString() + " km";
			}
		}
		else{
			button+=5;
			removeClass(document.getElementById("seta_esquerda_2"), "hidden");
			if (button >= maxLimit){
				button = maxLimit;
				document.getElementById("seta_direita_2").className = "hidden";
			}
			if (button === 0) {
				document.getElementById("35").firstChild.innerHTML = "Desligado";
			}
			else {
				document.getElementById("35").firstChild.innerHTML = button.toString() + " km";
			}
		}
	}
	else if (onMenu === 5) {
		if(key == 'a'){
			button--;
			removeClass(document.getElementById("seta_direita3"), "hidden");
			if (button <= minLimit){
				button = minLimit;
				document.getElementById("seta_esquerda3").className = "hidden";
			}
			document.getElementById("92").firstChild.innerHTML = button.toString() + "/" + maxLimit.toString();
		}
		else{
			button++;
			removeClass(document.getElementById("seta_esquerda3"), "hidden");
			if (button >= maxLimit){
				button = maxLimit;
				document.getElementById("seta_direita3").className = "hidden";
			}
			document.getElementById("92").firstChild.innerHTML = button.toString() + "/" + maxLimit.toString();
		}
		if (modelo_selecionado === 1) {
				document.getElementById("bancosIMG").firstChild.src = "images/carros/p" + button.toString() + ".png";
			}
			else if (modelo_selecionado === 2) {
				document.getElementById("bancosIMG").firstChild.src = "images/carros/m" + (button - 3).toString() + ".png";
			}
			else if (modelo_selecionado === 3) {
				document.getElementById("bancosIMG").firstChild.src = "images/carros/g" + (button - 6).toString() + ".png";
			}
	}
	else if (onMenu === 6) {
		if(key == 'a'){
			button--;
			removeClass(document.getElementById("seta_direita4"), "hidden");
			if (button <= minLimit){
				button = minLimit;
				document.getElementById("seta_esquerda4").className = "hidden";
			}
			document.getElementById("97").firstChild.innerHTML = possiveis_bagageiras[button];
		}
		else{
			button++;
			removeClass(document.getElementById("seta_esquerda4"), "hidden");
			if (button >= maxLimit){
				button = maxLimit;
				document.getElementById("seta_direita4").className = "hidden";
			}
			document.getElementById("97").firstChild.innerHTML = possiveis_bagageiras[button];
		}
		if (modelo_selecionado === 1) {
			document.getElementById("bagageiraIMG").firstChild.src = "images/carros/pb" + possiveis_bagageiras[button].substring(0,1) + ".png";
		}
		else if (modelo_selecionado === 2) {
			document.getElementById("bagageiraIMG").firstChild.src = "images/carros/b" + possiveis_bagageiras[button].substring(0,1) + ".png";
		}
		else if (modelo_selecionado === 3) {
			document.getElementById("bagageiraIMG").firstChild.src = "images/carros/b" + possiveis_bagageiras[button].substring(0,1) + ".png";
		}
		if (possiveis_bagageiras[button] === "Pequeno") {
			ajudas_menu[97] = "<br>    <u>"+possiveis_bagageiras[button]+"</u>:<br>    Tamanho mais pequeno<br>    da bagageira. Não permite<br>    muito espaço para<br>    compras, por exemplo.";
		}
		else if (possiveis_bagageiras[button] === "Médio") {
			ajudas_menu[97] = "<br>    <u>"+possiveis_bagageiras[button]+"</u>:<br>    Tamanho médio da<br>    bagageira. Tem espaço<br>    suficiente para muitas<br>    compras.";
		}
		else if (possiveis_bagageiras[button] === "Grande") {
			ajudas_menu[97] = "<br>    <u>"+possiveis_bagageiras[button]+"</u>:<br>    Maior tamanho possível<br>    da bagageira. Tem espaço<br>    suficiente para muitas<br>    mercadorias.";
		}
		actualizar_ajuda();
	}
});	

function change_pos_left(now, gone, midAfter, leftAfter) {
	var terminated = document.getElementById(gone);
	var reborn = document.getElementById(leftAfter);
	var actual = document.getElementById(now);
	var pro = document.getElementById(midAfter);
	terminated.className = "hidden";
	reborn.className = "item_left";
	actual.className = "item_right";
	pro.className = "item_mid";
	if (midAfter <= 9) {
		var text = document.getElementById("hidden_text");
		var legenda = document.getElementById("legenda_menu_geral");
		if (midAfter >= 3 && midAfter <= 8) {
			$('#legenda_menu_geral_imagem2').css('left', '25px');
		}
		else {
			$('#legenda_menu_geral_imagem2').css('left', '116px');
		}
	}
	else if (midAfter >= 13 && midAfter <= 16) {
		var text = document.getElementById("hidden_text2");
		var legenda = document.getElementById("legenda_combustivel_geral");
	}
	else if (midAfter >= 20 && midAfter <= 23) {
		var text = document.getElementById("hidden_text3");
		var legenda = document.getElementById("legenda_personalizar_geral");
		if (midAfter === "23") {
			$('#legenda_personalizar_geral_imagem2').css('left', '116px');
		}
		else {
			$('#legenda_personalizar_geral_imagem2').css('left', '163px');
		}
	}
	else if (midAfter >= 46 && midAfter <= 49) {
		var text = document.getElementById("hidden_text4");
		var legenda = document.getElementById("legenda_combustivel_criterio_bomba");
		if (midAfter === "49") {
			$('#legenda_combustivel_criterio_bomba_imagem2').css('left', '140px');
		}
		else {
			$('#legenda_combustivel_criterio_bomba_imagem2').css('left', '200px');
		}
	}
	else if (midAfter >= 63 && midAfter <= 66) {
		var text = document.getElementById("hidden_text5");
		var legenda = document.getElementById("legenda_paquimetro_metodo_pagamento");
	}
	else if (midAfter >= 87 && midAfter <= 89) {
		var text = document.getElementById("hidden_text6");
		var legenda = document.getElementById("legenda_personalizar_editar_modelo");
	}
	text.firstChild.innerHTML = opcoes_carrocel[midAfter];
	legenda.firstChild.innerHTML = legenda_carrocel[midAfter];
}

function change_pos_right(now, gone, midAfter, leftAfter) {
	var terminated = document.getElementById(gone);
	var reborn = document.getElementById(leftAfter);
	var actual = document.getElementById(now);
	var pro = document.getElementById(midAfter);
	terminated.className = "hidden";
	reborn.className = "item_right";
	actual.className = "item_left";
	pro.className = "item_mid";
	if (midAfter <= 9) {
		var text = document.getElementById("hidden_text");
		var legenda = document.getElementById("legenda_menu_geral");
		if (midAfter >= 3 && midAfter <= 8) {
			$('#legenda_menu_geral_imagem2').css('left', '25px');
		}
		else {
			$('#legenda_menu_geral_imagem2').css('left', '116px');
		}
	}
	else if (midAfter >= 13 && midAfter <= 16) {
		var text = document.getElementById("hidden_text2");
		var legenda = document.getElementById("legenda_combustivel_geral");
	}
	else if (midAfter >= 20 && midAfter <= 23) {
		var text = document.getElementById("hidden_text3");
		var legenda = document.getElementById("legenda_personalizar_geral");
		if (midAfter === "23") {
			$('#legenda_personalizar_geral_imagem2').css('left', '116px');
		}
		else {
			$('#legenda_personalizar_geral_imagem2').css('left', '163px');
		}
	}
	else if (midAfter >= 46 && midAfter <= 49) {
		var text = document.getElementById("hidden_text4");
		var legenda = document.getElementById("legenda_combustivel_criterio_bomba");
		if (midAfter === "49") {
			$('#legenda_combustivel_criterio_bomba_imagem2').css('left', '140px');
		}
		else {
			$('#legenda_combustivel_criterio_bomba_imagem2').css('left', '200px');
		}
	}
	else if (midAfter >= 63 && midAfter <= 66) {
		var text = document.getElementById("hidden_text5");
		var legenda = document.getElementById("legenda_paquimetro_metodo_pagamento");
	}
	else if (midAfter >= 87 && midAfter <= 89) {
		var text = document.getElementById("hidden_text6");
		var legenda = document.getElementById("legenda_personalizar_editar_modelo");
	}
	text.firstChild.innerHTML = opcoes_carrocel[midAfter];
	legenda.firstChild.innerHTML = legenda_carrocel[midAfter];
}

function select(id){
	var ele = document.getElementById(id);
	ele.className += " selected";
}
 
function deselect(id){ 
	var ele = document.getElementById(id);
	removeClass(ele, "selected");
} 
function removeClass(ele,cls) {
	var reg = new RegExp('(\\s|^)'+cls+'(\\s|$)');
	ele.className = ele.className.replace(reg,' ');
}

function precise_round(num,decimals){
	var sign = num >= 0 ? 1 : -1;
	return (Math.round((num*Math.pow(10,decimals))+(sign*0.001))/Math.pow(10,decimals)).toFixed(decimals);
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                                ///
///                                               Menu geral                                                       ///
///                                                                                                                ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

function menu_inicial() {
	$("#" + menu_anterior).hide(0);
	$("#" + menu_actual).hide(0);
	$(carousel_modelo_carro).show(0);
	onMenu = 1;
	button = 1;
	maxLimit = 9;
	minLimit = 0;
	for (var i = 0; i <= 9; i++) {
		if (i < 4) {
			document.getElementById(i.toString()).className = carrocel_class[i];
		}
		else {
			document.getElementById(i.toString()).className = "hidden";
		}
	}
	selected = "#" + button.toString();
	document.getElementById("hidden_text").firstChild.innerHTML = opcoes_carrocel[button];
	menu_actual = "carousel_modelo_carro";
	document.getElementById("legenda_menu_geral").firstChild.innerHTML = legenda_carrocel[button];
}

function menu_inicial_desligar() {
	menu_inicial();
	desligar();
}

function fechar_selecionado() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	menu_anterior = menu_actual;
	menu_inicial();
	actualizar_ajuda();
	document.getElementById("background_mapa").src = "images/mapas/mais_perto.png";
	desligar();
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                                ///
///                                               Combustivel                                                      ///
///                                                                                                                ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

var alerta = 20;
var favorita = "Galp";
var favourito_pos = 0;
var possiveis_favoritos = new Array();
possiveis_favoritos[0] = "Galp";
possiveis_favoritos[1] = "BP";
possiveis_favoritos[2] = "Repsol";
possiveis_favoritos[3] = "Cepsa";
possiveis_favoritos[4] = "Jumbo";
possiveis_favoritos[5] = "Total";
possiveis_favoritos[6] = "Shell";

function Combustivel() {
	$(carousel_modelo_carro).hide(0);
	$(carousel_combustivel).show(0);
	button = 14;
	maxLimit = 16;
	minLimit = 13;
	selected = "#" + button.toString();
	menu_actual = "carousel_combustivel";
	document.getElementById("legenda_combustivel_geral").firstChild.innerHTML =  "  Editar              Voltar atrás";
	actualizar_ajuda();
}


/*/////////////////////////////////////////////
////                                       ////
////          Mudar favorito               ////
////                                       ////
/////////////////////////////////////////////*/

function configurar_combustivel() {
	$(carousel_combustivel).hide(0);
	$(configurar_combustivel_marcas).show(0);
	onMenu = 2;
	button = 30;
	maxLimit = 31;
	minLimit = 30;
	select(button.toString());
	selected = "#" + button.toString();
	document.getElementById("30").firstChild.innerHTML = favorita;
	menu_actual = "configurar_combustivel_marcas";
	document.getElementById("31").innerHTML = "Voltar";
	document.getElementById("legenda_configurar_combustivel_marcas").firstChild.innerHTML = "   Editar marca favorita             Voltar atrás";
	document.getElementById("image_combustivel").firstChild.src = bombas_favoritas[favourito_pos];
}

function change_favourite() {
	removeClass(document.getElementById("seta_esquerda"),"hidden");
	removeClass(document.getElementById("seta_direita"),"hidden");
	onMenu = 3;
	button = favourito_pos;
	minLimit = 0;
	maxLimit = 6;
	selected = "#32";
	menu_actual = "mudar_favorito";
	document.getElementById("legenda_configurar_combustivel_marcas").firstChild.innerHTML = "   Guardar              <font color=FFA500>◄</font> ou <font color=FFA500>►</font> Altera a marca";
	$("#legenda_configurar_combustivel_marcas_imagem2").hide(0);
}
function return_change_favourite() {
	document.getElementById("seta_esquerda").className = "hidden";
	document.getElementById("seta_direita").className = "hidden";
	if (favorita !== possiveis_favoritos[button]) {
		document.getElementById("31").innerHTML = "Concluir";
	}
	favorita = possiveis_favoritos[button];
	favourito_pos = button;
	onMenu = 2;
	button = 30;
	maxLimit = 31;
	minLimit = 30;
	selected = "#" + button.toString();
	menu_actual = "configurar_combustivel_marcas";
	$("#legenda_configurar_combustivel_marcas_imagem2").show(0);
	document.getElementById("legenda_configurar_combustivel_marcas").firstChild.innerHTML = legendas_a_por[button];
}
function fechar_configuracao() {
	deselect("31");
	onMenu = 1;
	button = 13;
	maxLimit = 16;
	minLimit = 13;
	selected = "#" + button.toString();
	menu_actual = "carousel_combustivel";
	selected = "#" + button.toString();
	$(configurar_combustivel_marcas).hide(0);
	$(carousel_combustivel).show(0);							
}

/*/////////////////////////////////////////////
////                                       ////
////            Mudar autonomia            ////
////                                       ////
/////////////////////////////////////////////*/

function configurar_alerta() {
	$(carousel_combustivel).hide(0);
	$(configurar_alerta_km).show(0);
	onMenu = 2;
	button = 35;
	maxLimit = 36;
	minLimit = 35;
	select(button.toString());
	selected = "#" + button.toString();
	if (alerta === 0) {
		document.getElementById("35").firstChild.innerHTML = "Desligado";
	}
	else {
		document.getElementById("35").firstChild.innerHTML = alerta.toString() + " km";
	}
	menu_actual = "configurar_alerta_km";
	document.getElementById("legenda_configurar_combustivel_km").firstChild.innerHTML = "   Editar Km para o alerta           Voltar atrás";
}	

function change_alert() {
	removeClass(document.getElementById("seta_esquerda_2"),"hidden");
	removeClass(document.getElementById("seta_direita_2"),"hidden");
	onMenu = 4;
	button = alerta;
	minLimit = 0;
	maxLimit = 100;
	selected = "#37";
	menu_actual = "configurar_alerta_km_mudar";
	$("#legenda_configurar_combustivel_km_imagem2").hide(0);
	document.getElementById("legenda_configurar_combustivel_km").firstChild.innerHTML = "  Guardar              <font color=FFA500>◄</font> ou <font color=FFA500>►</font> Altera Km";
}

function return_change_alert() {
	document.getElementById("seta_esquerda_2").className = "hidden";
	document.getElementById("seta_direita_2").className = "hidden";
	if (button !== alerta) {
		document.getElementById("36").firstChild.innerHTML = "Concluir";
	}
	alerta = button;
	onMenu = 2;
	button = 35;
	maxLimit = 36;
	minLimit = 35;
	selected = "#" + button.toString();
	if (alerta === 0) {
		document.getElementById("35").firstChild.innerHTML = "Desligado";
	}
	else {
		document.getElementById("35").firstChild.innerHTML = alerta.toString() + " km";
	}
	menu_actual = "configurar_alerta_km";
	$("#legenda_configurar_combustivel_km_imagem2").show(0);
	document.getElementById("legenda_configurar_combustivel_km").firstChild.innerHTML = "   Editar Km para o alerta           Voltar atrás";
}

function fechar_configuracao2() {
	deselect("36");
	onMenu = 1;
	button = 14;
	maxLimit = 16;
	minLimit = 13;
	selected = "#" + button.toString();
	menu_actual = "carousel_combustivel";
	selected = "#" + button.toString();
	$(configurar_alerta_km).hide(0);
	$(carousel_combustivel).show(0);
	document.getElementById("36").firstChild.innerHTML = "Voltar";
}

/*/////////////////////////////////////////////
////                                       ////
////       Pop up - baixo combustivel      ////
////                                       ////
/////////////////////////////////////////////*/	

$(document).jkey('w',function(key){
	if (alerta !== 0) {
		alerta_combustivel_func();
		actualizar_ajuda();
	}
});

function ignorar_alerta_msg() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(ignorar_alerta_pop).show(0);
	onMenu = 2;
	minLimit =53;
	maxLimit = 54;
	button = 53;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "ignorar_alerta_pop";
	document.getElementById("legenda_combustivel_pop_up_ignora").firstChild.innerHTML = "   Sim                        Voltar atrás";
	actualizar_ajuda();
}

function como_escolher_bomba() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(escolher_criterio_bomba).show(0);
	onMenu = 1;
	minLimit = 46;
	maxLimit = 49;
	button = 47;
	selected = "#" + button.toString();
	menu_actual = "escolher_criterio_bomba";
	document.getElementById("legenda_combustivel_criterio_bomba").firstChild.innerHTML = "  Mostrar Bombas                Voltar atrás";
	actualizar_ajuda();
}

function mostrar_mapa_direcao() {
	if (button === 46) {
		document.getElementById("background_mapa").src = "images/mapas/Favorita/favorita_"+favorita+".png";
	}
	else if (button === 47) {
		document.getElementById("background_mapa").src = "images/mapas/mais_barata.png";
	}
	else if (button === 48) {
		document.getElementById("background_mapa").src = "images/mapas/mais_perto.png";
	}
	$(escolher_criterio_bomba).hide(0);
	$(Bombas_mapa_alerta).show(0);
	onMenu = 0;
	selected = "#51";
	menu_actual = "Bombas_mapa_alerta";
	document.getElementById("legenda_combustivel_bombas_mapa_alerta").firstChild.innerHTML = "  Fechar               Voltar atrás";
	actualizar_ajuda();
}
function alerta_combustivel_func() {
	deselect(button.toString());
	document.getElementById("aviso_combustivel_baixo").firstChild.innerHTML = "<br>Autonomia Restante: " + alerta.toString() + " km<br>Deseja obter informações sobre postos de combústivel?";
	$("#" + menu_actual).hide(0);
	$(alerta_combustivel).show(0);
	onMenu = 2;
	minLimit = 40;
	maxLimit = 41;
	button = 40;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "alerta_combustivel";
	document.getElementById("legenda_combustivel_pop_up").firstChild.innerHTML = "   Sim                        Voltar atrás";
	actualizar_ajuda();
}

function ignorar_alerta() {
	deselect(button.toString());
	menu_inicial();
	actualizar_ajuda();
	desligar();
}

/*/////////////////////////////////////////////
////                                       ////
////                 Mapas                 ////
////                                       ////
/////////////////////////////////////////////*/	

function mostrar_mapa() {
	$(carousel_combustivel).hide(0);
	$(Bombas_mapa_alerta).show(0);
	onMenu = 0;
	selected = "#44";
	menu_actual = "Bombas_mapa";
	document.getElementById("legenda_combustivel_bombas_mapa_alerta").firstChild.innerHTML = "  Fechar               Voltar atrás";
}

function sair_mapas() {
	$(Bombas_mapa_alerta).hide(0);
	$(carousel_combustivel).show(0);			
	onMenu = 1;
	button = 15;
	maxLimit = 16;
	minLimit = 13;
	selected = "#" + button.toString();
	menu_actual = "carousel_combustivel";
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                                ///
///                                               Personalizacao                                                   ///
///                                                                                                                ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


var modelo_activo = 2;
var modelo_selecionado = 2;
var bancos_pequeno = 1;
var bancos_pequeno_max = 3;
var bancos_medio = 5;
var bancos_medio_max = 6;
var bancos_grande = 7;
var bancos_grande_max = 9;

var bagageira_pequeno = "Pequeno";
var bagageira_medio = "Médio";
var bagageira_grande = "Grande";

var possiveis_bagageiras = new Array();
possiveis_bagageiras[0] = "Pequeno";
possiveis_bagageiras[1] = "Médio";
possiveis_bagageiras[2] = "Grande";

function Personalizar() {
	if (modelo_activo === 1) {
		document.getElementById("carro_pequeno_editar_imagem").src = "images/carro_pequeno_visto.png";
		document.getElementById("carro_medio_editar_imagem").src = "images/carro_medio.png";
		document.getElementById("carro_grande_editar_imagem").src = "images/carro_grande.png";
	}
	else if (modelo_activo === 2) {
		document.getElementById("carro_pequeno_editar_imagem").src = "images/carro_pequeno.png";
		document.getElementById("carro_medio_editar_imagem").src = "images/carro_medio_visto.png";
		document.getElementById("carro_grande_editar_imagem").src = "images/carro_grande.png";
	}
	else if (modelo_activo === 3) {
		document.getElementById("carro_pequeno_editar_imagem").src = "images/carro_pequeno.png";
		document.getElementById("carro_medio_editar_imagem").src = "images/carro_medio.png";
		document.getElementById("carro_grande_editar_imagem").src = "images/carro_grande_visto.png";
	}
	document.getElementById("hidden_text3").firstChild.innerHTML = "Médio";
	document.getElementById("legenda_personalizar_geral").firstChild.innerHTML = "    Activar/Editar              Voltar atrás";
	$(carousel_modelo_carro).hide(0);
	$(carousel_personalizar).show(0);
	onMenu = 1;
	button = 21;
	maxLimit = 23;
	minLimit = 20;
	selected = "#" + button.toString();
	menu_actual = "carousel_personalizar";
	actualizar_ajuda();
}		

function ActivarOuEditarModelo() {
	if (button === 20) modelo_selecionado = 1;
	else if (button === 21) modelo_selecionado = 2;
	else if (button === 22) modelo_selecionado = 3;
	if (modelo_selecionado === 1) {
		document.getElementById("modelo_a_editar_ativar").src = "images/carro_pequeno.png";
	}
	else if (modelo_selecionado === 2) {
		document.getElementById("modelo_a_editar_ativar").src = "images/carro_medio.png";
	}
	else if (modelo_selecionado === 3) {
		document.getElementById("modelo_a_editar_ativar").src = "images/carro_grande.png";
	}
	$("#" + menu_actual).hide(0);
	$(ActivarOuEditar).show(0);
	onMenu = 2;
	minLimit = 82;
	maxLimit = 84;
	button = 82;
	selected = "#" + button.toString();
	select(button.toString());
	document.getElementById("legenda_personalizar_geral_activar_editar").firstChild.innerHTML = "    Activar                           Voltar atrás";
	menu_actual = "ActivarOuEditar";
}

function CancelarActivarEditar() {
	$("#" + menu_actual).hide(0);
	deselect(button.toString());
	Personalizar();
	button = 19 + modelo_selecionado;
}

function QuerActivarModelo(){
	modelo_activo = modelo_selecionado;
	if (modelo_selecionado === 1) {
		document.getElementById("modelo_a_editar_ativar").src = "images/carro_pequeno.png";
		document.getElementById("ModoAtivado").firstChild.innerHTML = "<br><br>Modo pequeno activado<br>";
	}
	else if (modelo_selecionado === 2) {
		document.getElementById("modelo_a_editar_ativar").src = "images/carro_medio.png";
		document.getElementById("ModoAtivado").firstChild.innerHTML = "<br><br>Modo médio activado<br>";
	}
	else if (modelo_selecionado === 3) {
		document.getElementById("modelo_a_editar_ativar").src = "images/carro_grande.png";
		document.getElementById("ModoAtivado").firstChild.innerHTML = "<br><br>Modo grande activado<br>";
	}
	$(ActivarOuEditar).hide(0);
	$(ConcluidoAtivarModelo).show(0);
	deselect(button.toString());
	var j = 0;
	for (var i = 20; i <= 23; i++) {
		if (j < 4) {
			document.getElementById(i.toString()).className = carrocel_class[j];
		}
		else {
			document.getElementById(i.toString()).className = "hidden";
		}
		j++;
	}	
	setTimeout(function() { 
		$(ConcluidoAtivarModelo).hide(0); 
		menu_inicial();
		desligar();
		actualizar_ajuda();
	}, 2000);
	
}

function QuerEditarModelo() {
	deselect(button.toString());
	$(ActivarOuEditar).hide(0);
	$(carousel_editar_modelo).show(0);
	button = 88;
	minLimit = 87;
	maxLimit = 89;
	onMenu = 1;
	selected = "#" + button.toString();
	menu_actual = "carousel_editar_modelo";
	document.getElementById("hidden_text6").firstChild.innerHTML = opcoes_carrocel[button];
	document.getElementById("legenda_personalizar_editar_modelo").firstChild.innerHTML = "   Editar             Voltar atrás";
	actualizar_ajuda();
}

function ActivarEditarBagageira() {
	document.getElementById("98").firstChild.innerHTML = "Voltar";
	$(carousel_editar_modelo).hide(0);
	$(EditarBagagem).show(0);
	if (modelo_selecionado === 1) {
		document.getElementById("97").firstChild.innerHTML = bagageira_pequeno;
		document.getElementById("bagageiraIMG").firstChild.src = "images/carros/pb" + bagageira_pequeno.substring(0,1) + ".png";
		if (bagageira_pequeno === "Pequeno") {
			ajudas_menu[97] = "<br>    <u>"+bagageira_pequeno+"</u>:<br>    Tamanho mais pequeno<br>    da bagageira. Não permite<br>    muito espaço para<br>    compras, por exemplo.";
		}
		else if (bagageira_pequeno === "Médio") {
			ajudas_menu[97] = "<br>    <u>"+bagageira_pequeno+"</u>:<br>    Tamanho médio da<br>    bagageira. Tem espaço<br>    suficiente para muitas<br>    compras.";
		}
	}
	else if (modelo_selecionado === 2) {
		document.getElementById("97").firstChild.innerHTML = bagageira_medio;
		document.getElementById("bagageiraIMG").firstChild.src = "images/carros/b" + bagageira_medio.substring(0,1) + ".png";
		if (bagageira_medio === "Pequeno") {
			ajudas_menu[97] = "<br>    <u>"+bagageira_medio+"</u>:<br>    Tamanho mais pequeno<br>    da bagageira. Não permite<br>    muito espaço para<br>    compras, por exemplo.";
		}
		else if (bagageira_medio === "Médio") {
			ajudas_menu[97] = "<br>    <u>"+bagageira_medio+"</u>:<br>    Tamanho médio da<br>    bagageira. Tem espaço<br>    suficiente para muitas<br>    compras.";
		}
		else if (bagageira_medio === "Grande") {
			ajudas_menu[97] = "<br>    <u>"+bagageira_medio+"</u>:<br>    Maior tamanho possível<br>    da bagageira. Tem espaço<br>    suficiente para muitas<br>    mercadorias.";
		}
	}
	else if (modelo_selecionado === 3) {
		document.getElementById("97").firstChild.innerHTML = bagageira_grande;
		document.getElementById("bagageiraIMG").firstChild.src = "images/carros/b" + bagageira_grande.substring(0,1) + ".png";
		if (bagageira_grande === "Pequeno") {
			ajudas_menu[97] = "<br>    <u>"+bagageira_grande+"</u>:<br>    Tamanho mais pequeno<br>    da bagageira. Não permite<br>    muito espaço para<br>    compras, por exemplo.";
		}
		else if (bagageira_grande === "Médio") {
			ajudas_menu[97] = "<br>    <u>"+bagageira_grande+"</u>:<br>    Tamanho médio da<br>    bagageira. Tem espaço<br>    suficiente para muitas<br>    compras.";
		}
		else if (bagageira_grande === "Grande") {
			ajudas_menu[97] = "<br>    <u>"+bagageira_grande+"</u>:<br>    Maior tamanho possível<br>    da bagageira. Tem espaço<br>    suficiente para muitas<br>    mercadorias.";
		}
	}
	onMenu = 2;
	button = 97;
	maxLimit = 98;
	minLimit = 97;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "EditarBagagem";
	document.getElementById("legenda_editar_bagagem").firstChild.innerHTML = "   Editar Tamanho                    Voltar Atrás";
	actualizar_ajuda();
}	

function ActivarEditarBancos() {
	document.getElementById("93").firstChild.innerHTML = "Voltar";
	$(carousel_editar_modelo).hide(0);
	$(EditarBancos).show(0);
	if (modelo_selecionado === 1) {
		document.getElementById("92").firstChild.innerHTML = bancos_pequeno.toString() + "/" + bancos_pequeno_max.toString();
		document.getElementById("bancosIMG").firstChild.src = "images/carros/p" + bancos_pequeno.toString() + ".png";
	}
	else if (modelo_selecionado === 2) {
		document.getElementById("92").firstChild.innerHTML = bancos_medio.toString() + "/" + bancos_medio_max.toString();
		document.getElementById("bancosIMG").firstChild.src = "images/carros/m" + (bancos_medio-3).toString() + ".png";
	}
	else if (modelo_selecionado === 3) {
		document.getElementById("92").firstChild.innerHTML = bancos_grande.toString() + "/" + bancos_grande_max.toString();
		document.getElementById("bancosIMG").firstChild.src = "images/carros/g" + (bancos_grande-6).toString() + ".png";
	}
	onMenu = 2;
	button = 92;
	maxLimit = 93;
	minLimit = 92;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "EditarBancos";
	document.getElementById("legenda_editar_bancos").firstChild.innerHTML = "   Editar número                           Voltar Atrás";
	actualizar_ajuda();
}

function mudar_bancos() {
	if (modelo_selecionado === 1) {
		button = bancos_pequeno;
		minLimit = 1;
		maxLimit = 3;
	}
	else if (modelo_selecionado === 2) {
		button = bancos_medio;
		minLimit = 4;
		maxLimit = 6;
	}
	else if (modelo_selecionado === 3) {
		button = bancos_grande;
		minLimit = 7;
		maxLimit = 9;
	}
	if (button === maxLimit) {
		removeClass(document.getElementById("seta_esquerda3"),"hidden");
	}
	else if (button === minLimit) {
		removeClass(document.getElementById("seta_direita3"),"hidden");
	} 
	else {
		removeClass(document.getElementById("seta_esquerda3"),"hidden");
		removeClass(document.getElementById("seta_direita3"),"hidden");
	}
	onMenu = 5;
	selected = "#94";
	menu_actual = "mudar_bancos";
	$("#legenda_editar_bancos_imagem2").hide(0);
	document.getElementById("legenda_editar_bancos").firstChild.innerHTML = "   Guardar              <font color=FFA500>◄</font> ou <font color=FFA500>►</font> Alterar os bancos";
}

function return_mudar_bancos() {
	document.getElementById("seta_esquerda3").className = "hidden";
	document.getElementById("seta_direita3").className = "hidden";
	if (modelo_selecionado === 1) {
		if (button !== bancos_pequeno) {
			document.getElementById("93").firstChild.innerHTML = "Concluir";
			bancos_pequeno = button;
		}
		onMenu = 2;
		button = 92;
		maxLimit = 93;
		minLimit = 92;
		selected = "#" + button.toString();
		menu_actual = "EditarBancos";
	}
	else if (modelo_selecionado === 2) {
		if (button !== bancos_medio) {
			document.getElementById("93").firstChild.innerHTML = "Concluir";
			bancos_medio = button;
		}
		onMenu = 2;
		button = 92;
		maxLimit = 93;
		minLimit = 92;
		selected = "#" + button.toString();
		menu_actual = "EditarBancos";
	}
	else if (modelo_selecionado === 3) {
		if (button !== bancos_grande) {
			document.getElementById("93").firstChild.innerHTML = "Concluir";
			bancos_grande = button;
		}
		onMenu = 2;
		button = 92;
		maxLimit = 93;
		minLimit = 92;
		selected = "#" + button.toString();
		menu_actual = "EditarBancos";
	}
	$("#legenda_editar_bancos_imagem2").show(0);
	document.getElementById("legenda_editar_bancos").firstChild.innerHTML = "   Editar número                           Voltar Atrás";
}

function mudar_bagageira() {
	removeClass(document.getElementById("seta_esquerda4"),"hidden");
	removeClass(document.getElementById("seta_direita4"),"hidden");
	if (modelo_selecionado === 1) {
		if (bagageira_pequeno === "Pequeno") {
			button = 0;
			minLimit = 0;
			maxLimit = 1;
		}
		else if (bagageira_pequeno === "Médio") {
			button = 1;
			minLimit = 0;
			maxLimit = 1;
		}
	}
	else if (modelo_selecionado === 2) {
		if (bagageira_medio === "Pequeno") {
			button = 0;
			minLimit = 0;
			maxLimit = 2;
		}
		else if (bagageira_medio === "Médio") {
			button = 1;
			minLimit = 0;
			maxLimit = 2;
		}
		else {
			button = 2;
			minLimit = 0;
			maxLimit = 2;
		}
	}
	else if (modelo_selecionado === 3) {
		if (bagageira_grande === "Pequeno") {
			button = 0;
			minLimit = 0;
			maxLimit = 2;
		}
		else if (bagageira_grande === "Médio") {
			button = 1;
			minLimit = 0;
			maxLimit = 2;
		}
		else {
			button = 2;
			minLimit = 0;
			maxLimit = 2;
		}
	}
	onMenu = 6;
	selected = "#99";
	menu_actual = "mudar_bagageira";
	$("#legenda_editar_bagagem_imagem2").hide(0);
	document.getElementById("legenda_editar_bagagem").firstChild.innerHTML = "   Guardar              <font color=FFA500>◄</font> ou <font color=FFA500>►</font> Alterar o tamanho";
}

function return_mudar_bagageira() {
	document.getElementById("seta_esquerda4").className = "hidden";
	document.getElementById("seta_direita4").className = "hidden";
	if (modelo_selecionado === 1) {
		if (possiveis_bagageiras[button] !== bagageira_pequeno) {
			document.getElementById("98").firstChild.innerHTML = "Concluir";
			bagageira_pequeno = possiveis_bagageiras[button];
		}
		onMenu = 2;
		button = 97;
		maxLimit = 98;
		minLimit = 97;
		selected = "#" + button.toString();
		menu_actual = "EditarBagagem";
	}
	else if (modelo_selecionado === 2) {
		if (possiveis_bagageiras[button] !== bagageira_medio) {
			document.getElementById("98").firstChild.innerHTML = "Concluir";
			bagageira_medio = possiveis_bagageiras[button];
		}
		onMenu = 2;
		button = 97;
		maxLimit = 98;
		minLimit = 97;
		selected = "#" + button.toString();
		menu_actual = "EditarBagagem";
	}
	else if (modelo_selecionado === 3) {
		if (possiveis_bagageiras[button] !== bagageira_grande) {
			document.getElementById("98").firstChild.innerHTML = "Concluir";
			bagageira_grande = possiveis_bagageiras[button];
		}
		onMenu = 2;
		button = 97;
		maxLimit = 98;
		minLimit = 97;
		selected = "#" + button.toString();
		menu_actual = "EditarBagagem";
	}
	$("#legenda_editar_bagagem_imagem2").show(0);
	document.getElementById("legenda_editar_bagagem").firstChild.innerHTML = "   Editar Tamanho                    Voltar Atrás";
}

function SairBancos() {
	deselect(button.toString());
	$(EditarBancos).hide(0);
	$(carousel_editar_modelo).show(0);
	button = 88;
	minLimit = 87;
	maxLimit = 89;
	onMenu = 1;
	selected = "#" + button.toString();
	menu_actual = "carousel_editar_modelo";
	actualizar_ajuda();
}

function SairBagageira() {
	deselect(button.toString());
	$(EditarBagagem).hide(0);
	$(carousel_editar_modelo).show(0);
	button = 87;
	minLimit = 87;
	maxLimit = 89;
	onMenu = 1;
	selected = "#" + button.toString();
	menu_actual = "carousel_editar_modelo";
	actualizar_ajuda();
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                                ///
///                                               Paquimetro                                                       ///
///                                                                                                                ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

var begin = new Date();
var end;
var diff;
var valor;

$(document).jkey('q',function(key){
	menu_paquimetro();
});

function menu_paquimetro() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(MenuDoParque).show(0);
	onMenu = 2;
	minLimit = 26;
	maxLimit = 27;
	button = 26;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "MenuDoParque";
	document.getElementById("legenda_paquimetro_pop_up").firstChild.innerHTML = "   Iniciar                      Sair";
	actualizar_ajuda();
}

function IniciarParque(){
	begin = new Date();
	$(MenuDoParque).hide(0);
	$(AContar).show(0);
	$(ImagemAContar).show(0);
	deselect(button.toString());
	button = 60;
	onMenu = 0;
	selected = "#" + button.toString();
	select(button.toString());
	menu_anterior = "ImagemAContar";
	menu_actual = "AContar";
	document.getElementById("legenda_paquimetro_pop_up2").firstChild.innerHTML = "   Parar              Sair";
	actualizar_ajuda();
}

function IgnorarParque(){
	$(MenuDoParque).hide(0);
	$(popup_estacionamento_ignora).show(0);
	deselect(button.toString());
	onMenu = 2;
	button = 57;
	maxLimit = 58;
	minLimit = 57;
	selected = "#" + button.toString();
	select(button.toString());
	menu_actual = "popup_estacionamento_ignora";
	document.getElementById("legenda_paquimetro_pop_up_ignora").firstChild.innerHTML = "   Sim                        Voltar atrás";
	actualizar_ajuda();
}

function PararAContagem() {
	end = new Date();
	diff = end.getTime() - begin.getTime();
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$("#" + menu_anterior).hide(0);
	$(MetodoPagamento).show(0);
	diff = diff/(1000*60);
	valor = precise_round((diff*0.02), 2);
	document.getElementById("ex").firstChild.innerHTML = "<br>A Pagar: " + valor + "€. Metodo de pagamento: ";
	onMenu = 1;
	minLimit = 63;
	maxLimit = 66;
	button = 64;
	selected = "#" + button.toString();
	menu_actual = "MetodoPagamento";
	document.getElementById("legenda_paquimetro_metodo_pagamento").firstChild.innerHTML = legenda_carrocel[button];
	actualizar_ajuda();
}

$(document).jkey('e',function(key){
	if (menu_actual === "AContar") {
		end = new Date();
		diff = end.getTime() - begin.getTime();
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$("#" + menu_anterior).hide(0);
		$(MetodoPagamento).show(0);
		diff = diff/(10*60);
		valor = precise_round((diff*0.02), 2);
		document.getElementById("ex").firstChild.innerHTML = "<br>A Pagar: " + valor + "€. Metodo de pagamento: ";
		onMenu = 1;
		minLimit = 63;
		maxLimit = 66;
		button = 64;
		selected = "#" + button.toString();
		menu_actual = "MetodoPagamento";
		actualizar_ajuda();
	}
});

function QuerIgnorar(){
	deselect(button.toString());
	menu_inicial();
	actualizar_ajuda();
}

function NaoQuerIgnorar(){
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(MenuDoParque).show(0);
	onMenu = 2;
	minLimit = 26;
	maxLimit = 27;
	button = 26;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "MenuDoParque";
	actualizar_ajuda();
}

function continuar_a_contar() {
	$("#" + menu_actual).hide(0);
	$(AContar).show(0);
	$(ImagemAContar).show(0);
	deselect(button.toString());
	button = 60;
	onMenu = 0;
	selected = "#" + button.toString();
	select(button.toString());
	menu_anterior = "ImagemAContar";
	menu_actual = "AContar";
	actualizar_ajuda();
}

function n_continuar_a_contar() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(MetodoPagamento).show(0);
	onMenu = 1;
	minLimit = 63;
	maxLimit = 66;
	button = 64;
	selected = "#" + button.toString();
	menu_actual = "MetodoPagamento";
	actualizar_ajuda();
}

function PagarDebito() {
	$("#" + menu_actual).hide(0);
	$(PagarComDebito).show(0);
	document.getElementById("ex2").firstChild.innerHTML = "<br>Vão ser cobrados " + valor + "€ da sua conta.<br>";
	onMenu = 2;
	minLimit = 71;
	maxLimit = 72;
	button = 71;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "PagarComDebito";
	document.getElementById("legenda_paquimetro_metodo_pagamento_debito").firstChild.innerHTML = " Aceitar            Voltar atrás";
	actualizar_ajuda();
}

function QuerConfirmarDebito() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(ConcluidoPagamentoDebito).show(0);
	setTimeout(function (){ $(ConcluidoPagamentoDebito).hide(0); desligar();}, 2000);
	var j = 0;
	for (var i = 63; i <= 66; i++) {
		if (j < 4) {
			document.getElementById(i.toString()).className = carrocel_class[j];
		}
		else {
			document.getElementById(i.toString()).className = "hidden";
		}
		j++;
	}
}

function QuerCancelarDebito() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(MetodoPagamento).show(0);
	onMenu = 1;
	minLimit = 63;
	maxLimit = 66;
	button = 64;
	selected = "#" + button.toString();
	menu_actual = "MetodoPagamento";
	actualizar_ajuda();
}

function PagarDinheiro() {
	$("#" + menu_actual).hide(0);
	$(PagarComDinheiro).show(0);
	document.getElementById("ex3").firstChild.innerHTML = "<br>Dirija-se ao paquímetro mais próximo<br>e pague " + valor + "€ .";
	document.getElementById("legenda_paquimetro_metodo_pagamento_dinheiro").firstChild.innerHTML = "   Confirmar               Voltar atrás";
	onMenu = 2;
	minLimit = 75;
	maxLimit = 76;
	button = 75;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "PagarComDinheiro";
	actualizar_ajuda();
}

function QuerConfirmarDinheiro() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(ConcluidoPagamentoDinheiro).hide(0); 
	$(mapa_pagamento).show(0);
	onMenu = 0;
	button = 77;
	selected = "#" + button.toString();	
	menu_actual = "mapa_pagamento";
	document.getElementById("legenda_paquimetro_metodo_pagamento_dinheiro_mapa").firstChild.innerHTML = " Fechar            Voltar atrás";
	actualizar_ajuda();
	var j = 0;
	for (var i = 63; i <= 66; i++) {
		if (j < 4) {
			document.getElementById(i.toString()).className = carrocel_class[j];
		}
		else {
			document.getElementById(i.toString()).className = "hidden";
		}
		j++;
	}
	
}

function QuerCancelarDinheiro() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(MetodoPagamento).show(0);
	onMenu = 1;
	minLimit = 63;
	maxLimit = 66;
	button = 63;
	selected = "#" + button.toString();
	menu_actual = "MetodoPagamento";
	actualizar_ajuda();
}

function PagarNosCTT() {
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(PagarCTT).show(0);
	document.getElementById("ex4").firstChild.innerHTML = "<br>Deseja pagar " + valor + "€ através dos CTT?<br>";
	document.getElementById("legenda_paquimetro_metodo_pagamento_CTT").firstChild.innerHTML = " Aceitar            Voltar atrás";
	onMenu = 2;
	minLimit = 79;
	maxLimit = 80;
	button = 79;
	select(button.toString());
	selected = "#" + button.toString();
	menu_actual = "PagarCTT";
	actualizar_ajuda();
}

function QuerConfirmarCTT(){
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(ConcluidoPagamentoDinheiro).show(0);
	setTimeout(function (){ $(ConcluidoPagamentoDinheiro).hide(0); desligar(); }, 2000);
	var j = 0;
	for (var i = 63; i <= 66; i++) {
		if (j < 4) {
			document.getElementById(i.toString()).className = carrocel_class[j];
		}
		else {
			document.getElementById(i.toString()).className = "hidden";
		}
		j++;
	}
}

function QuerCancelarCTT(){
	deselect(button.toString());
	$("#" + menu_actual).hide(0);
	$(MetodoPagamento).show(0);
	onMenu = 1;
	minLimit = 63;
	maxLimit = 66;
	button = 65;
	selected = "#" + button.toString();
	menu_actual = "MetodoPagamento";
	actualizar_ajuda();
}

function desligar() {
	$("#" + menu_actual).hide(0);
	$("#" + menu_anterior).hide(0);
	onMenu = -1;
	menu_actual = "desligado";
	$("#desligado").show(0);
	document.getElementById("legenda_menu_desligado").firstChild.innerHTML = "   Ligar";
	$("#ajuda_menus").hide(0);
	$('.menus').css('background-image', 'url(images/2.png)');
	ajuda_activa = 0;
	actualizar_ajuda();
}

/*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                                ///
///                                               Atalhos teclado                                                  ///
///                                                                                                                ///
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

$(document).jkey('k',function(key){
	if (menu_actual != "desligado") {
		$(selected).click();
	}
	else {
		menu_inicial();
	}
});

$(document).jkey('o',function(key){
	menu_inicial();
	actualizar_ajuda();
});

$(document).jkey('p',function(key){
	$("#" + menu_actual).hide(0);
	$("#" + menu_anterior).hide(0);
	onMenu = 0;
});

$(document).jkey('l',function(key){
	if (menu_actual === "carousel_combustivel") {
		$(carousel_combustivel).hide(0);
		$(carousel_modelo_carro).show(0);
		button = 1;
		maxLimit = 9;
		minLimit = 0;
		selected = "#" + button.toString();
		menu_actual = "carousel_modelo_carro";
		actualizar_ajuda();
	}
	else if (menu_actual === "carousel_modelo_carro") {
		desligar();
		actualizar_ajuda();
	}
	else if(menu_actual === "carousel_personalizar") {
		$(carousel_personalizar).hide(0);
		$(carousel_modelo_carro).show(0);
		var j = 0;
		for (var i = 20; i < 24; i++) {
			if (j < 4) {
				document.getElementById(i.toString()).className = carrocel_class[j];
			}
			else {
				document.getElementById(i.toString()).className = "hidden";
			}
			j++;
			document.getElementById("hidden_text3").firstChild.innerHTML = "Medio";
		}
		$('#legenda_personalizar_geral_imagem2').css('left', '163px');
		onMenu = 1;
		button = 0;
		maxLimit = 9;
		minLimit = 0;
		selected = "#" + button.toString();
		menu_actual = "carousel_modelo_carro";
		actualizar_ajuda();
	}
	else if(menu_actual === "configurar_combustivel_marcas") {
		deselect(button.toString());
		$(configurar_combustivel_marcas).hide(0);
		$(carousel_combustivel).show(0);
		onMenu = 1;
		button = 13;
		maxLimit = 16;
		minLimit = 13;
		selected = "#" + button.toString();
		menu_actual = "carousel_combustivel";
		actualizar_ajuda();
	}
	else if(menu_actual === "mudar_favorito") {
		document.getElementById("seta_esquerda").className = "hidden";
		document.getElementById("seta_direita").className = "hidden";
		document.getElementById("30").firstChild.innerHTML = favorita;
		document.getElementById("image_combustivel").firstChild.src = bombas_favoritas[favourito_pos];
		onMenu = 2;
		button = 30;
		maxLimit = 31;
		minLimit = 30;
		selected = "#" + button.toString();
		menu_actual = "configurar_combustivel_marcas";
		$("#legenda_configurar_combustivel_marcas_imagem2").show(0);
		document.getElementById("legenda_configurar_combustivel_marcas").firstChild.innerHTML = "   Editar marca favorita             Voltar atrás";
		actualizar_ajuda();
	}
	
	else if(menu_actual === "configurar_alerta_km") {
		deselect(button.toString());
		$(configurar_alerta_km).hide(0);
		$(carousel_combustivel).show(0);
		onMenu = 1;
		button = 14;
		maxLimit = 16;
		minLimit = 13;
		selected = "#" + button.toString();
		menu_actual = "carousel_combustivel";
		actualizar_ajuda();
	}
	
	else if(menu_actual === "configurar_alerta_km_mudar") {
		document.getElementById("seta_esquerda_2").className = "hidden";
		document.getElementById("seta_direita_2").className = "hidden";
		if (alerta === 0) {
			document.getElementById("35").firstChild.innerHTML = "Desligado";
		}
		else {
			document.getElementById("35").firstChild.innerHTML = alerta.toString() + " km";
		}
		onMenu = 2;
		button = 35;
		maxLimit = 36;
		minLimit = 35;
		selected = "#" + button.toString();
		menu_actual = "configurar_alerta_km";
		$("#legenda_configurar_combustivel_km_imagem2").hide(0);
		document.getElementById("legenda_configurar_combustivel_km").firstChild.innerHTML = "   Editar Km para o alerta           Voltar atrás";
		actualizar_ajuda();
	}
	else if(menu_actual === "Bombas_mapa") {
		deselect(button.toString());
		$(Bombas_mapa_alerta).hide(0);
		$(carousel_combustivel).show(0);			
		onMenu = 1;
		button = 15;
		maxLimit = 16;
		minLimit = 13;
		selected = "#" + button.toString();
		menu_actual = "carousel_combustivel";
		actualizar_ajuda();
	}
	else if(menu_actual === "alerta_combustivel") {
		ignorar_alerta_msg();
		actualizar_ajuda();
	}
	else if(menu_actual === "ignorar_alerta_pop") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(alerta_combustivel).show(0);
		onMenu = 2;
		minLimit = 40;
		maxLimit = 41;
		button = 40;
		select(button.toString());
		selected = "#" + button.toString();
		menu_actual = "alerta_combustivel";
		actualizar_ajuda();
	}
	else if(menu_actual === "escolher_criterio_bomba") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(alerta_combustivel).show(0);
		onMenu = 2;
		minLimit = 40;
		maxLimit = 41;
		button = 40;
		select(button.toString());
		selected = "#" + button.toString();
		menu_actual = "alerta_combustivel";
		var j = 0;
		for (var i = 46; i < 50; i++) {
			if (j < 4) {
				document.getElementById(i.toString()).className = carrocel_class[j];
			}
			else {
				document.getElementById(i.toString()).className = "hidden";
			}
			j++;
			document.getElementById("hidden_text4").firstChild.innerHTML = "Mais barata";
		}
		actualizar_ajuda();
	}
	else if(menu_actual === "Bombas_mapa_alerta") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(escolher_criterio_bomba).show(0);
		onMenu = 1;
		minLimit = 46;
		maxLimit = 49;
		selected = "#" + button.toString();
		menu_actual = "escolher_criterio_bomba";
		actualizar_ajuda();
	}
	else if (menu_actual === "MenuDoParque") {
		IgnorarParque();
		actualizar_ajuda();
	}
	else if (menu_actual === "popup_estacionamento_ignora") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(MenuDoParque).show(0);
		onMenu = 2;
		minLimit = 26;
		maxLimit = 27;
		button = 26;
		select(button.toString());
		selected = "#" + button.toString();
		menu_actual = "MenuDoParque";
		actualizar_ajuda();
	}
	else if(menu_actual === "AContar") {
		var endif_ = new Date();
		var diff_ = endif_.getTime() - begin.getTime();
		if ((diff_/1000) < 60) {
			deselect(button.toString());
			menu_inicial();
		}
		actualizar_ajuda();
	}
	else if (menu_actual === "MetodoPagamento") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(popup_continuar_contar).show(0);
		onMenu = 2;
		button = 68;
		maxLimit = 69;
		minLimit = 68;
		select(button.toString());
		selected = "#" + button.toString();
		menu_actual = "popup_continuar_contar";
		document.getElementById("legenda_paquimetro_continuar_a_contar").firstChild.innerHTML = "   Sim                        Voltar atrás";
		actualizar_ajuda();
	}
	else if (menu_actual === "popup_continuar_contar") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(MetodoPagamento).show(0);
		onMenu = 1;
		minLimit = 63;
		maxLimit = 66;
		button = 64;
		selected = "#" + button.toString();
		menu_actual = "MetodoPagamento";
		actualizar_ajuda();
	}
	else if (menu_actual === "PagarComDebito") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(MetodoPagamento).show(0);
		onMenu = 1;
		minLimit = 63;
		maxLimit = 66;
		button = 64;
		selected = "#" + button.toString();
		menu_actual = "MetodoPagamento";
		actualizar_ajuda();
	}
	else if (menu_actual === "PagarComDinheiro") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(MetodoPagamento).show(0);
		onMenu = 1;
		minLimit = 63;
		maxLimit = 66;
		button = 63;
		selected = "#" + button.toString();
		menu_actual = "MetodoPagamento";
		actualizar_ajuda();
	}
	else if (menu_actual === "PagarCTT") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(MetodoPagamento).show(0);
		onMenu = 1;
		minLimit = 63;
		maxLimit = 66;
		button = 65;
		selected = "#" + button.toString();
		menu_actual = "MetodoPagamento";
		actualizar_ajuda();
	}
	else if (menu_actual === "EditarBancos") {
		deselect(button.toString());
		$(EditarBancos).hide(0);
		$(carousel_editar_modelo).show(0);
		button = 88;
		minLimit = 87;
		maxLimit = 89;
		onMenu = 1;
		selected = "#" + button.toString();
		menu_actual = "carousel_editar_modelo";
		actualizar_ajuda();
	}
	else if (menu_actual === "EditarBagagem") {
		deselect(button.toString());
		$(EditarBagagem).hide(0);
		$(carousel_editar_modelo).show(0);
		button = 87;
		minLimit = 87;
		maxLimit = 89;
		onMenu = 1;
		selected = "#" + button.toString();
		menu_actual = "carousel_editar_modelo";
		actualizar_ajuda();
	}
	else if (menu_actual === "mudar_bancos") {
		deselect(button.toString());
		document.getElementById("seta_esquerda3").className = "hidden";
		document.getElementById("seta_direita3").className = "hidden";
		if (modelo_selecionado === 1) {
			document.getElementById("92").innerHTML = bancos_pequeno.toString() + "/" + bancos_pequeno_max.toString();
			onMenu = 2;
			button = 92;
			maxLimit = 93;
			minLimit = 92;
			selected = "#" + button.toString();
			menu_actual = "EditarBancos";
		}
		else if (modelo_selecionado === 2) {
			document.getElementById("92").innerHTML = bancos_medio.toString() + "/" + bancos_medio_max.toString();
			onMenu = 2;
			button = 92;
			maxLimit = 93;
			minLimit = 92;
			selected = "#" + button.toString();
			menu_actual = "EditarBancos";
		}
		else if (modelo_selecionado === 3) {
			document.getElementById("92").innerHTML = bancos_grande.toString() + "/" + bancos_grande_max.toString();
			onMenu = 2;
			button = 92;
			maxLimit = 93;
			minLimit = 92;
			selected = "#" + button.toString();
			menu_actual = "EditarBancos";
		}
		$("#legenda_editar_bancos_imagem2").show(0);
		document.getElementById("legenda_editar_bancos").firstChild.innerHTML = "   Editar número                           Voltar Atrás";
		actualizar_ajuda();
	}
	else if (menu_actual === "mudar_bagageira") {
		document.getElementById("seta_esquerda4").className = "hidden";
		document.getElementById("seta_direita4").className = "hidden";
		if (modelo_selecionado === 1) {
			document.getElementById("97").firstChild.innerHTML = bagageira_pequeno;
			onMenu = 2;
			button = 97;
			maxLimit = 98;
			minLimit = 97;
			selected = "#" + button.toString();
			menu_actual = "EditarBagagem";
		}
		else if (modelo_selecionado === 2) {
			document.getElementById("97").firstChild.innerHTML = bagageira_medio;
			onMenu = 2;
			button = 97;
			maxLimit = 98;
			minLimit = 97;
			selected = "#" + button.toString();
			menu_actual = "EditarBagagem";
		}
		else if (modelo_selecionado === 3) {
			document.getElementById("97").firstChild.innerHTML = bagageira_grande;
			onMenu = 2;
			button = 97;
			maxLimit = 98;
			minLimit = 97;
			selected = "#" + button.toString();
			menu_actual = "EditarBagagem";
		}
		$("#legenda_editar_bagagem_imagem2").show(0);
		document.getElementById("legenda_editar_bagagem").firstChild.innerHTML = "   Editar Tamanho                    Voltar Atrás";
		actualizar_ajuda();
	}
	else if (menu_actual === "carousel_editar_modelo") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		$(ActivarOuEditar).show(0);
		onMenu = 2;
		minLimit = 82;
		maxLimit = 84;
		button = 83;
		selected = "#" + button.toString();
		select(button.toString());
		menu_actual = "ActivarOuEditar";
		var j = 0;
		for (var i = 87; i <= 89; i++) {
			if (j < 4) {
				document.getElementById(i.toString()).className = carrocel_class[j];
			}
			else {
				document.getElementById(i.toString()).className = "hidden";
			}
			j++;
		}
		actualizar_ajuda();
	}
	else if (menu_actual === "ActivarOuEditar") {
		deselect(button.toString());
		$("#" + menu_actual).hide(0);
		if (modelo_activo === 1) {
			document.getElementById("carro_pequeno_editar_imagem").src = "images/carro_pequeno_visto.png";
			document.getElementById("carro_medio_editar_imagem").src = "images/carro_medio.png";
			document.getElementById("carro_grande_editar_imagem").src = "images/carro_grande.png";
		}
		else if (modelo_activo === 2) {
			document.getElementById("carro_pequeno_editar_imagem").src = "images/carro_pequeno.png";
			document.getElementById("carro_medio_editar_imagem").src = "images/carro_medio_visto.png";
			document.getElementById("carro_grande_editar_imagem").src = "images/carro_grande.png";
		}
		else if (modelo_activo === 3) {
			document.getElementById("carro_pequeno_editar_imagem").src = "images/carro_pequeno.png";
			document.getElementById("carro_medio_editar_imagem").src = "images/carro_medio.png";
			document.getElementById("carro_grande_editar_imagem").src = "images/carro_grande_visto.png";
		}
		document.getElementById("hidden_text3").firstChild.innerHTML = "Médio";
		document.getElementById("legenda_personalizar_geral").firstChild.innerHTML = "    Activar/Editar              Voltar atrás";
		$(carousel_personalizar).show(0);
		onMenu = 1;
		maxLimit = 23;
		minLimit = 20;
		selected = "#" + button.toString();
		menu_actual = "carousel_personalizar";
		if (modelo_selecionado === 1) {
			button = 20;
			document.getElementById("hidden_text3").firstChild.innerHTML = "Pequeno";
		}
		else if (modelo_selecionado === 2) {
			button = 21;
			document.getElementById("hidden_text3").firstChild.innerHTML = "Médio";
		}
		else if (modelo_selecionado === 3) {
			button = 22;
			document.getElementById("hidden_text3").firstChild.innerHTML = "Grande";
		}
		actualizar_ajuda();
	}
});
