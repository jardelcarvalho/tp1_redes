#include "truco.h"

//! Funções
Baralho* new_baralho(){
	Baralho* baralho = malloc(sizeof(Baralho));

	int naipe, valor;
	for (naipe = 0; naipe < 4; naipe++){ 
		for (valor = 0; valor < 10; valor++){ 
			baralho->cartas[naipe*10+valor].numero= valor+1;
			baralho->cartas[naipe*10+valor].naipe = naipe;
			baralho->ordem[naipe*10+valor] = naipe*10+valor;
		}
	}

	return baralho;
}

void print_carta(Carta carta){
	char valor;

	// Definindo o numero da carta a ser exibido
	if(carta.numero == 1){
		valor = 'A';
	}else if(carta.numero == 8){
		valor = 'Q';
	}else if(carta.numero == 9){
		valor = 'J';
	}else if(carta.numero == 10){
		valor = 'K';
	}else{
		valor = carta.numero + '0';
	}

	// Definindo o naipe a ser exibido
	if(carta.naipe == COPAS){
		printf("[%c \u2665]", valor);
	}else if(carta.naipe == OUROS){
		printf("[%c \u2666]", valor);
	}else if(carta.naipe == PAUS){
		printf("[%c \u2663]", valor);
	}else{ // ESPADAS
		printf("[%c \u2660]", valor);
	}
}

void print_carta_sock(Carta carta, int fd) {
	char valor;
	char buffer[_BUFF_TAM];
	memset(buffer, '\0', _BUFF_TAM);

	// Definindo o numero da carta a ser exibido
	if(carta.numero == 1){
		valor = 'A';
	}else if(carta.numero == 8){
		valor = 'Q';
	}else if(carta.numero == 9){
		valor = 'J';
	}else if(carta.numero == 10){
		valor = 'K';
	}else{
		valor = carta.numero + '0';
	}

	// Definindo o naipe a ser exibido
	if(carta.naipe == COPAS){
		sprintf(buffer, "[%c \u2665]", valor);
	}else if(carta.naipe == OUROS){
		sprintf(buffer, "[%c \u2666]", valor);
	}else if(carta.naipe == PAUS){
		sprintf(buffer, "[%c \u2663]", valor);
	}else{ // ESPADAS
		sprintf(buffer, "[%c \u2660]", valor);
	}
	envia_UI(fd, buffer);
}

void print_baralho(Baralho baralho, int qnt_cartas){
	int i;
	for (i = 0; i < qnt_cartas; i++){ 
		print_carta(baralho.cartas[
			baralho.ordem[i]
		]);
		
		(i != qnt_cartas-1)?printf(", "): printf("\n");
	}
}

void print_mao_player(Jogador player, Baralho baralho){
	int i;
	char buffer[_BUFF_TAM];
	memset(buffer, '\0', _BUFF_TAM);
	for(i = 0; i < QNT_MAO; i++){
		if(player.mao[i] == ((uint8_t)-1)) {
			continue;
		}
		
		sprintf(buffer, "%d:", i); 
		envia_UI(player.sockfd, buffer); 
		print_carta_sock(baralho.cartas[player.mao[i]], player.sockfd);
		(i != QNT_MAO - 1) ? sprintf(buffer, ", ") : sprintf(buffer, "\n"); 
		envia_UI(player.sockfd, buffer); 
	}
}

void embaralhar(Baralho *baralho){
	int max_swap = 1000;

	srand(time(NULL));
	for(; max_swap > 0; max_swap--){
		int aux;
		int carta1 = rand()%QNT_CARTAS,
			carta2 = rand()%QNT_CARTAS; 

		aux = baralho->ordem[carta1];
		baralho->ordem[carta1] = baralho->ordem[carta2];
		baralho->ordem[carta2] = aux;
	}
}

void distribuir_cartas(Baralho baralho, int *inicio, Jogador *player){
	int i;
	for(i=0; i < QNT_MAO; i++, (*inicio)++){
		player->mao[i]= baralho.ordem[(*inicio)%QNT_CARTAS];
	}
}

int rank_carta(Carta carta){
	/* Manilhas do truco */
	if(carta.numero == 4 && carta.naipe == PAUS)
		return 0;
	if(carta.numero == 7 && carta.naipe == COPAS)
		return 1;
	if(carta.numero == 1 && carta.naipe == ESPADAS)
		return 2;
	if(carta.numero == 7 && carta.naipe == OUROS)
		return 3;

	/* Outras cartas do baralho */
	switch(carta.numero){
		case 3: return 4;
		case 2: return 5;
		case 1: return 6;
		case 10: return 7;
		case 9: return 8;
		case 8: return 9;
		case 7: return 10;
		case 6: return 11;
		case 5: return 12;
		case 4: return 13;
	}

	return -1;
}

int maior_carta(Carta carta1, Carta carta2){
	return rank_carta(carta1) - rank_carta(carta2);
}

/*++====================================================++*/
/*||                                                    ||*/
/*||                        TRUCO                       ||*/
/*||                                                    ||*/
/*++====================================================++*/
int pedir_truco(Jogador p1, Jogador p2, int aposta) {
	char buffer[2 * _BUFF_TAM];
	memset(buffer, '\0', _BUFF_TAM);
	sprintf(buffer, " Escolha !!\n");
	envia_UI(p2.sockfd, buffer);
	if(aposta != 12) {
		sprintf(buffer, "\t3. Aumentar\n");
		envia_UI(p2.sockfd, buffer);
	}
	sprintf(buffer, "\t4. Aceitar\n\t5. Recusar\n");
	envia_UI(p2.sockfd, buffer);
	
	int acao;
	do{
		sprintf(buffer, "$> ");
		envia_UI(p2.sockfd, buffer);
		//printf("$> ");
		acao = get_acao (p2);
	}while(!(acao & (ACEITAR | AUMENTAR | RECUSAR)));

	if(acao & AUMENTAR){
		sprintf(buffer, "%s pediu para aumentar a aposta\n", p2.nome);
		envia_UI(p1.sockfd, buffer);
		if(aposta == 12) {
			return aposta;
		}
		return pedir_truco(p2, p1, aumentar_aposta(p1, aposta));
	}else if(acao & ACEITAR){
		sprintf(buffer, "%s aceitou a aposta\n", p2.nome);
		envia_UI(p1.sockfd, buffer);
		return aposta;
	}

	sprintf(buffer, "%s recusou a aposta\n", p2.nome);
	envia_UI(p1.sockfd, buffer);
	// Recusei a aposta do cidadao
	return recusar_aposta(p2, aposta) * (-1);
}

void print_mao_player_de_10(Jogador player, Jogador destinatario, Baralho baralho) {
	int i;
	char buffer[_BUFF_TAM];
	memset(buffer, '\0', _BUFF_TAM);
	for(i = 0; i < QNT_MAO; i++){
		if(player.mao[i] == ((uint8_t)-1)) {
			continue;
		}
		print_carta_sock(baralho.cartas[player.mao[i]], destinatario.sockfd);
		(i != QNT_MAO - 1) ? sprintf(buffer, ", ") : sprintf(buffer, "\n");
		envia_UI(destinatario.sockfd, buffer);
	}
}

int isMao10(int pontos[2], Jogador players[4], int qnt_pl, Baralho b){
	int i;
	int mao10 = 0;
	char buffer[_BUFF_TAM * 2];
	memset(buffer, '\0', _BUFF_TAM * 2);

	for(i = 0; i < 2; i++){
		if(pontos[i] == 10){
			char opcao;

			sprintf(buffer, "%s: ", "Sua mão: ");
			envia_UI(players[i].sockfd, buffer);
			print_mao_player_de_10(players[i], players[i], b);

			sprintf(buffer, "%s: ", "Mão do seu parceiro: ");
			envia_UI(players[i].sockfd, buffer);
			print_mao_player_de_10(players[i + 2], players[i], b);
			
			if(qnt_pl > 2){
				sprintf(buffer, "%s: ", "Sua mão: ");
				envia_UI(players[i + 2].sockfd, buffer);
				print_mao_player_de_10(players[i + 2], players[i + 2], b);

				sprintf(buffer, "%s: ", "Mão do seu parceiro\0");
				envia_UI(players[i].sockfd, buffer);
				print_mao_player_de_10(players[i], players[i + 2], b);
			}

			sprintf(buffer, "Ir para a mao de 10 %s?[Y/N]\n", players[i].nome);
			envia_UI(players[i].sockfd, buffer);
			int loop = 1;
			while(loop) {
				switch(recebe_UI(players[i].sockfd)[0]) {
					case 'n':
						pontos[1] += 2;
						return -1;
					case 'N':
						pontos[1] += 2;
						return -1;
					case 'y':
						loop = 0;
						break;
					case 'Y':
						loop = 0;
						break;
					default:
						continue;
				}
			}
			mao10 = 1;
		}
	}

	return mao10;
}

int gera_rodada(Jogador players[4], int qnt_player, Baralho *deck, int rodada, int mao_10){

	int i;
	int player_atual;
	int player_acao = -1;
	int player_trucou = -1;
	int player_vencedor = -1;
	int aposta = 2; 
	
	char buffer[2 * _BUFF_TAM];
	memset(buffer, '\0', 2 * _BUFF_TAM);

	if(mao_10){
		aposta = 4;
	}

	// Se a posição for -1, então foi empate
	// Se a posição for  0, então o time 1 venceu
	// Se a posição for  1, então o time 2 venceu
	int8_t vencedor_rodada[3] = {-1, -1, -1};

	/* Para as três cartas que serão jogadas */
	for(i = 0; i < 3; i++){
		int melhor_carta = -1;
		if(player_vencedor == -1) player_vencedor = rodada;
		player_atual = player_vencedor;
		
		//Para cada jogada de um player
		int player, player_rodada = player_vencedor;
		for(player = 0; player < qnt_player; player++){
			player_atual = (player_rodada+player)%qnt_player;

			/* Informa os outros jogadores quem está jogando nesta iteração */
			sprintf(buffer, "(#) %s está jogando\n", players[player_atual].nome);
			for(int i = 0; i < qnt_player; i++) {
				if(i != player_atual) {
					envia_UI(players[i].sockfd, buffer);
				}
			}

			/* Informa ao player que está jogando qual a sua mão */	
			sprintf(buffer, "\nSua vez -> ");
			envia_UI(players[player_atual].sockfd, buffer);
			print_mao_player(players[player_atual], *deck);

			/* Pergunta ao player atual qual aposta ele pode escolher */
			if(aposta != 12 && player_trucou != player_atual % 2 && !mao_10) {
				sprintf(buffer, "3: pedir %s\n$> ", prox_aposta(aposta));
				envia_UI(players[player_atual].sockfd, buffer);
			}

			/* Recebe ação do jogador */
			player_acao = get_acao(players[player_atual]);
			if(player_acao == -1) {
				// Se a opção escolhida pelo jogador for inválida
				player--;
				continue;
			}

			/* Jogador querendo jogar uma carta */
			if(player_acao & JOGAR) {
				int result = 1;
				int carta = jogar_carta(&players[player_atual], player_acao & 3);
				
				if(carta == -1) {
					player--;
				}

				if(melhor_carta != -1) {
					result = maior_carta(deck->cartas[melhor_carta], deck->cartas[carta]);
				}

				if(result == 1) {
					melhor_carta = carta;
					player_vencedor = player_atual;
				}else if(result == 0){
					if(player_vencedor % 2 != player_atual % 2){
						player_vencedor = -1;
					}
				}

				/* Notifica os outros players a carta jogada pelo player atual e a carta vencedora até o momento */
				for(int i = 0; i < qnt_player; i++) {
					if(i != player_atual) {
						sprintf(buffer, "   %s jogou ", players[player_atual].nome);
						envia_UI(players[i].sockfd, buffer);
						print_carta_sock(deck->cartas[carta], players[i].sockfd);
						sprintf(buffer, "\n");
						envia_UI(players[i].sockfd, buffer);
						sprintf(buffer, "   ");
						envia_UI(players[i].sockfd, buffer);
						print_carta_sock(deck->cartas[melhor_carta], players[i].sockfd);
						sprintf(buffer, " é a melhor até o momento !\n");
						envia_UI(players[i].sockfd, buffer);						
					}
				}

			}else if(player_acao & AUMENTAR) {
				if(mao_10) { 
					return (player_atual % 2 == 0) ? aposta : -aposta;
				}
				if(aposta != 12 && player_trucou != player_atual % 2) { 
					player_trucou = player_atual % 2;
					aposta = pedir_truco(players[player_atual], players[(player_atual + 1) % qnt_player], aumentar_aposta(players[(player_atual + 1) % qnt_player], aposta));
					if(aposta < 0){
						if(player_atual % 2 == 0) return aposta;
						return aposta * (-1);
					}
				}
				player--; continue;
			}else{
				player--; continue;
			}
		}

		if(player_vencedor != -1){
			if( i != 0 && (vencedor_rodada[0] == -1 || vencedor_rodada[0] == player_vencedor % 2)){
				return (player_vencedor % 2 == 0 ? -aposta : aposta);
			}

			vencedor_rodada[i] = player_vencedor % 2;
		}else if(vencedor_rodada[0] != -1){
			return (player_vencedor % 2 == 0) ? -aposta : aposta;
		}
	}

	int somatorio = vencedor_rodada[0] + vencedor_rodada[1] + vencedor_rodada[2];

	if(somatorio == -3) {
		return 0; //Empatou tudo
	} else if(somatorio <= 1) {
		return aposta * -1;
	} else {
		return aposta;
	}
}

void envia_UI_padrao(Jogador jogadores[4], int qnt_jogadores, Baralho *deck, int pontos[2]) {
	char buffer[5 * _BUFF_TAM];
	memset(buffer, '\0', 5 * _BUFF_TAM);
	/* Enviando comando de clear para os clientes */
	buffer[0] = '*';
	for(int i = 0; i < qnt_jogadores; i++) {
		envia_UI(jogadores[i].sockfd, buffer);
	}

	/* Mensagem de boas vindas ao jogo de truco */
	for(int i = 0; i < qnt_jogadores; i++) {
		sprintf(buffer, "BEM VINDO AO TRUCO !!\n");
		envia_UI(jogadores[i].sockfd, buffer);
		if(strchr(jogadores[i].nome, '\n')) {
			*strchr(jogadores[i].nome, '\n') = '\0';
		}
	}
	
	/* Enviando placares e notificando cada jogador qual é o seu time */
	if(qnt_jogadores == 2) {
		sprintf(buffer, "# %s, seu adversário é %s\n", jogadores[0].nome, jogadores[1].nome);
		envia_UI(jogadores[0].sockfd, buffer);
		sprintf(buffer, "# %s, seu adversário é %s\n", jogadores[1].nome, jogadores[0].nome);
		envia_UI(jogadores[1].sockfd, buffer);

		sprintf(buffer, "Pontuacao: <[%s: %d, %s: %d]>\n\n", jogadores[0].nome, pontos[0], jogadores[1].nome, pontos[1]);
		for(int i = 0; i < 2; i++) {
			envia_UI(jogadores[i].sockfd, buffer);
		}
	} else {
		for(int i = 0; i < qnt_jogadores; i++) {
			if(i % 2 == 0) {
				sprintf(buffer, "# Seu time é o A: %s, %s. O time adversário é o B: %s, %s\n", jogadores[0].nome, jogadores[2].nome, jogadores[1].nome, jogadores[3].nome);
				envia_UI(jogadores[i].sockfd, buffer);
			} else {
				sprintf(buffer, "# Seu time é o B: %s, %s. O time adversário é o A: %s, %s\n", jogadores[1].nome, jogadores[3].nome, jogadores[0].nome, jogadores[2].nome);
				envia_UI(jogadores[i].sockfd, buffer);
			}
		}
		sprintf(buffer, "Pontuacao dos times: <[A: %d, B: %d]>\n\n", pontos[0], pontos[1]);
		for(int i = 0; i < qnt_jogadores; i++) {
			envia_UI(jogadores[i].sockfd, buffer);
		}
	}
}

/* Retorna 1 se a equipe 1 vencer e 2 caso a segunda */
int truco(Jogador jogadores[4], int qnt_jogadores){
	if(qnt_jogadores != 2 && qnt_jogadores != 4){
		printf("Nao é possivel jogar com essa configuracao de jogadores");
		return -4;
	}

	int player, rodada = 0;
	int pontos[2] = {0, 0};

	Baralho *baralho = new_baralho();

	/* Loop do jogo: enquanto alguém não venceu */
	while(pontos[0] != 12 && pontos[1] != 12){
		embaralhar(baralho);
		int corte_no_baralho = 0;

		// Distribuindo as cartas para os jogadores
		for(player = 0; player < qnt_jogadores; player++){
			distribuir_cartas(*baralho, &corte_no_baralho, &(jogadores[player]));
		}

		envia_UI_padrao(jogadores, qnt_jogadores, baralho, pontos);

		int mao10 = isMao10(pontos, jogadores, qnt_jogadores, *baralho);
		if(mao10 == -1) continue; // Alguém recusou a mão de 10

		// Rodada de cartas para os jogadores
		int pontuacao = gera_rodada(jogadores, qnt_jogadores, baralho, rodada, mao10);

		// Definindo os pontos para a equipe de jogadores
		pontos[pontuacao >= 0] = ((pontuacao >= 0) ? 1 : -1) * pontuacao;

		// Atualizando a rodada
		rodada = (rodada + 1) % qnt_jogadores;
	}

	return (pontos[0] == 12) ? 1 : 2;
}