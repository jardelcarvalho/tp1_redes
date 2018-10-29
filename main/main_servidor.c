#include "header_padrao.h"
#include "configura_socket.h"
#include "servidor.h"
#include "truco.h"

int main(int argc, char **argv) {
    
    char buffer[_BUFF_TAM];
    int fd_serv, fd_cli;
    socklen_t tam_ender_cliente;
    struct sockaddr_in serv_ender, cli_ender;
   
    if(configura_socket_servidor(&fd_serv, argv[1][0] - '0', &serv_ender) == -1) {
        return -1;
    }

    tam_ender_cliente = sizeof(serv_ender);
    int num_jogadores_esperados = argv[1][0] - '0';

    Jogador *clientes = recebe_clientes(fd_serv, num_jogadores_esperados, tam_ender_cliente);

    Jogador jogadores[4];
    for(int i = 0; i < num_jogadores_esperados; i++) {
        jogadores[i] = clientes[i];
    }

    /* Jogo */
    printf("#### Iniciando Jogo");
    truco(jogadores, num_jogadores_esperados);

    /* Fechando descritor de arquivo do servidor e dos jogadores */
    close(fd_serv);
    for(int i = 0; i < num_jogadores_esperados; i++) {
        close(jogadores[i].sockfd);
    }

    return 0;
}