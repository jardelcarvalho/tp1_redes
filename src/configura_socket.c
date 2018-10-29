#include "configura_socket.h"

int configura_socket_cliente(int *fd, struct sockaddr_in *ender) {
    //fd será configurado como o descritor de arquivos do servidor
    //ender é o endereço do servidor que será configurado para
    // o estabelecimento da conexão.
    ender = malloc(sizeof(struct sockaddr_in));
    /* Criando enderet e estabelecendo conexão com o servidor */
    if((*fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Erro ao executar enderet()\n");
        return -1;
    }

    memset(ender, '0', sizeof(*ender));

    ender->sin_family = AF_INET;
    ender->sin_port = htons(_PORTA);

    if(inet_pton(AF_INET, _IP, &(ender->sin_addr)) <= 0) {
        printf("Erro ao executar inet_pton()\n");
        return -1;
    }

    if(connect(*fd, (struct sockaddr *) ender, sizeof(*ender)) == -1) {
        printf("Erro ao executar connect()\n");
        return -1;
    }
    /* Criação do socket bem sucedida */
    return 0;
}


int configura_socket_servidor(int *fd, int num_clientes, struct sockaddr_in *ender) {
    //fd será configurado como o descritor de arquivos do servidor
    //ender é o endereço do servidor que ainda irá fazer o accept dos
    // clientes.
    ender = malloc(sizeof(struct sockaddr_in));
    /* Criando socket do servidor e configurando */
    if((*fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Erro ao executar socket()\n");
        return -1;
    }

    memset(ender, '0', sizeof(*ender));

    ender->sin_family = AF_INET; 
    ender->sin_addr.s_addr = INADDR_ANY;
    ender->sin_port = htons(_PORTA);

    if(bind(*fd, (struct sockaddr *) ender, sizeof(*ender)) == -1) {
        printf("Erro ao executar bind()\n");
        return -1;
    }

    if(listen(*fd, num_clientes) == -1) {
        printf("Erro ao executar listen()\n");
        return -1;
    }

    /* Criação do socket bem sucedida */
    return 0;
}