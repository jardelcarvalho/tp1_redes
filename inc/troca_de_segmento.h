#ifndef _TROCA_DE_SEGMENTO_H_
#define _TROCA_DE_SEGMENTO_H_

#include "header_padrao.h"

void envia_segmento(int fd, char *buffer, int tam_buffer);

void recebe_segmento(int fd, char *buffer, int tam_buffer);

#endif