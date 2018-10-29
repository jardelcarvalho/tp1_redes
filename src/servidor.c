#include "servidor.h"
#include "troca_de_segmento.h"

Jogador *recebe_clientes(int fd_serv, int num_clientes, socklen_t tam_ender_cliente) {
    //Com base no número de clientes e no tamanho do endereço de cada um
    // o loop abaixo representa a espera do servidor por todos os clientes/jogadores
    // que farão parte do jogo.
    char *msg = "Bem vindo ao jogo !\nEstamos montando equipes para que você possa jogar.\nPor favor aguade ...", buffer[_BUFF_TAM];
    struct sockaddr_in cli_ender;
    int fd_cli;
    Jogador *clientes = malloc(num_clientes * sizeof(Cliente));

    for(int i = 0; i < num_clientes; i++) {
        if((fd_cli = accept(fd_serv, (struct sockaddr *) &cli_ender, (socklen_t *) &tam_ender_cliente)) == -1) {
            printf("Erro ao executar accept()\n");
            return NULL;
        }
        clientes[i].sockfd = fd_cli;
        recebe_segmento(fd_cli, clientes[i].nome, _BUFF_TAM);
        printf("Recebeu jogador: %s\n", &clientes[i].nome[0]);
        memset(&buffer, '\0', _BUFF_TAM);
        strcpy(buffer, msg);
        envia_segmento(fd_cli, buffer, _BUFF_TAM);
    }
    //Execução concluída com sucesso
    return clientes;
}