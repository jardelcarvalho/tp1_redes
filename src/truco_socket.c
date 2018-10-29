#include "truco_socket.h"

void envia_UI(int fd, char *ui) {
    //Envia uma interface para o jogador imprimir na tela.
    char buffer[_BUFF_TAM];
    memset(buffer, '\0', _BUFF_TAM);
    strcpy(buffer, ui);
    envia_segmento(fd, buffer, _BUFF_TAM);
}

char *recebe_UI(int fd) {
    //Usada pelo jogador para receber a interface.
    char *buffer = malloc((_BUFF_TAM) * sizeof(char));
    memset(buffer, '\0', _BUFF_TAM); //por causa do '\0'
    recebe_segmento(fd, buffer, _BUFF_TAM);
    return buffer;
}

void envia_OPT(int fd, int opt) {
    //Usada pelo jogador para enviar uma opção de acordo
    // com a interface recebida.
    char buffer[_BUFF_TAM];
    memset(buffer, '\0', _BUFF_TAM);
    buffer[0] = (char) '0' + opt;
    envia_segmento(fd, buffer, _BUFF_TAM);
}

int recebe_OPT(int fd) {
    //Usada pelo servidor para receber a opção escolhida pelo jogador.
    char buffer[_BUFF_TAM];
    memset(buffer, '\0', _BUFF_TAM);
    recebe_segmento(fd, buffer, _BUFF_TAM);
    if(buffer[0] == '\0') {
        return -1;
    }
    return buffer[0] - '0';
}