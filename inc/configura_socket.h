#ifndef _CONFIGURA_SOCKET_H_
#define _CONFIGURA_SOCKET_H_

#include "header_padrao.h"

int configura_socket_cliente(int *fd, struct sockaddr_in *ender);
int configura_socket_servidor(int *fd, int num_clientes, struct sockaddr_in *ender);

#endif