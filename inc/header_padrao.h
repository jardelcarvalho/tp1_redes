#ifndef _HEADER_PADRAO_H_
#define _HEADER_PADRAO_H_

	/* Bibliotecas de manipulação de IO e variáveis */
	#include <stdio.h>
	#include <stdlib.h>
	#include <inttypes.h>
	#include <time.h>

	/* Bibliotacas de erros */
	#include <err.h>

	/* Bibliotecas de comunicação */
	#include <sys/socket.h>

	/* Bibliotecas de manipulação de Sockets */
	#include <sys/socket.h>
	#include <sys/types.h>
	#include <arpa/inet.h>
	#include <unistd.h>

	/* Bibliotecas de manipulação de Strings */
	#include <string.h>

	/* Definições importantes */
	typedef unsigned int socket_t;
	#define _PORTA 8080
	#define _BUFF_TAM 1024
	#define _NUM_CLIENTES 4
	#define _IP "127.0.0.1"

	typedef struct {
		/* Tamanho do nome do player conforme o #define acima
		os outros 3 bytes incrementados no vetor do nome são 
		reservados para se inserir \r\n\0 */
    	char nome[_BUFF_TAM];
		/* Descritor de arquivos correspondente ao socket 
		do cliente */
    	int fd;
		/* Endereço do cliente */
    	struct sockaddr_in ender;
	} Cliente;

#endif // _HEADER_PADRAO_H_