#ifndef _JOGADOR_H_
#define _JOGADOR_H_

	/* Bibliotecas */
	#include "header_padrao.h"
	#include "truco_socket.h"

	/* Definições */
	typedef enum{
		// 0,1,2 estão reservados para o índice 
		// da carta na mão do jogador
		JOGAR = 4,  // Jogar uma carta, valores até 40
		AUMENTAR = 8, // Aumentar aposta, truco, 6, etc
		ACEITAR = 16, // Aceitar aposta 
		RECUSAR = 32, // Recusar aposta
	}Acoes;

	typedef struct{
		socket_t sockfd;
		char nome[_BUFF_TAM];
		uint8_t mao[3];
	} Jogador;

	/* Funções */
	int jogada(Jogador *p1, int opcao);

	int aumentar_aposta(Jogador player, int aposta);

	char* prox_aposta(int aposta);

	int recusar_aposta(Jogador player, int aposta);

	int jogar_carta(Jogador *p1, int index_carta);// 0, 1 ou 2

	int get_acao(Jogador player);
	
#endif // _JOGADOR_H_