#ifndef _TRUCO_SOCKET_H_
#define _TRUCO_SOCKET_H_

#include "header_padrao.h"
#include "troca_de_segmento.h"

void envia_UI(int fd, char *ui);

char *recebe_UI(int fd);

void envia_OPT(int fd, int opt);

int recebe_OPT(int fd);

#endif