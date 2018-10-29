#include "jogador.h"

int jogada(Jogador *p1, int opcao){
	switch(opcao){
		case 3:
			return AUMENTAR;
		case 4:
			return ACEITAR;
		case 5:
			return RECUSAR;
	}
	
	/* Msg de jogar uma carta */
	if( opcao >= 0 && opcao <= 2){
		return JOGAR | opcao;
	}
	char buffer[_BUFF_TAM];
	memset(buffer, '\0', _BUFF_TAM);
	sprintf(buffer, "Opção não conhecida!!\n");
	envia_UI(p1->sockfd, buffer);
	return -1;
}

int aumentar_aposta(Jogador player, int aposta){
	char buffer[_BUFF_TAM];
	memset(buffer, '\0', _BUFF_TAM);
	switch(aposta){
		case 2:
			sprintf(buffer, "Adversário diz: TRUCO !!!\n");
			envia_UI(player.sockfd, buffer);
			return aposta+2;
		case 4:
			sprintf(buffer, "Adversário diz: Vem no SEIS !!!\n");
			envia_UI(player.sockfd, buffer);
			return aposta+4;
		case 8:
			sprintf(buffer, "Adversário diz: Quero ver é NOVE !!!\n");
			envia_UI(player.sockfd, buffer);
			return aposta+2;
		case 10:
			sprintf(buffer, "Adversário diz: Vamos ver de DOZE então !!!\n");
			envia_UI(player.sockfd, buffer);
			return aposta+2;
	}

	return -1;
}

char* prox_aposta(int aposta){
	switch(aposta){
		case 2: return "TRUCO";
		case 4: return "SEIS";
		case 8: return "NOVE";
		case 10: return "DOZE";
	}

	return "";
}

int recusar_aposta(Jogador player, int aposta){
	switch(aposta){
		case 4: return aposta - 2;
		case 8: return aposta - 4;
		case 10: return aposta - 2;
		case 12: return aposta - 2;
	}

	return -1;
}

int jogar_carta(Jogador *p1, int index_carta){
	if(p1->mao[index_carta] == -1) return -1;

	int carta = p1->mao[index_carta]; 
	p1->mao[index_carta] = -1;

	return carta;
}

/* Aqui é onde faz a leitura do socket para pegar a ação */
int get_acao(Jogador player){
	int opcao;

	char buffer[_BUFF_TAM];
	memset(buffer, '\0', _BUFF_TAM);
	buffer[0] = '%';
	envia_UI(player.sockfd, buffer);
	int aguardando = 1;
	while(aguardando) {
		opcao = recebe_OPT(player.sockfd);
		if(opcao != -1) {
			aguardando = 0;
		}
	}
	
	return jogada(&player, opcao);
}