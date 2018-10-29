#ifndef _TRUCO_H_
#define _TRUCO_H_

	/* Bibliotecas */
	#include "jogador.h"
	#include "header_padrao.h"
	#include "truco_socket.h"

	/* Definições */
	#define QNT_CARTAS 40

	#define QNT_MAO 3

	/* Definições de variáveis e estruturas */
	//! Estruturas
	//? Definição do conjunto de naipes
	typedef enum{
		//* Naipes: C-♥; O-♦; P-♣; E-♠
		COPAS = 0, OUROS, PAUS, ESPADAS
	}Naipe;

	//? Definição de uma carta do baralho 
	typedef struct{
		/* Para o jogo de truco os valores 
		1, 8, 9, 10, possui representações especiais, 
		respectivamente A, Q, J, K */
		// Valores: 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
		uint8_t numero;
		Naipe naipe;
	}Carta;

	#define _JOGADA '1'
	//? Definição de um baralho
	typedef struct{
		Carta cartas[QNT_CARTAS];
		uint8_t ordem[QNT_CARTAS];
	} Baralho;

	/* Funções */
	Baralho* new_baralho();

	void print_mao_player_de_10(Jogador player, Jogador destinatario, Baralho baralho);

	void envia_UI_padrao(Jogador jogadores[4], int qnt_jogadores, Baralho *deck, int pontos[2]);

	void print_baralho(Baralho baralho, int qnt_cartas);

	void print_carta(Carta carta);

	void print_carta_sock(Carta carta, int fd);

	void print_mao_player(Jogador player, Baralho baralho);

	void embaralhar(Baralho *baralho);

	void distribuir_cartas(Baralho baralho, int *inicio, Jogador *player);

	/* Retorna -1 se a carta1 é maior, 1 se é a carta2 e 
	0 se empate */
	int maior_carta(Carta carta1, Carta carta2);

	int truco(Jogador jogadores[4], int qnt_jogadores);

	int rank_carta(Carta carta);

	int maior_carta(Carta carta1, Carta carta2);

	int pedir_truco(Jogador p1, Jogador p2, int aposta);

	int isMao10(int pontos[2], Jogador players[4], int qnt_pl, Baralho b);

	int gera_rodada(Jogador players[4], int qnt_player, Baralho *deck, int rodada, int mao_10);

	int truco(Jogador jogadores[4], int qnt_jogadores);

#endif // _TRUCO_H_