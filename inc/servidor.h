#ifndef _SERVIDOR_H_
#define _SERVIDOR_H_

#include "header_padrao.h"
#include "truco_socket.h"
#include "jogador.h"

Jogador *recebe_clientes(int fd_serv, int num_clientes, socklen_t tam_ender_cliente);

#endif