#include "header_padrao.h"
#include "configura_socket.h"
#include "cliente.h"
#include "truco_socket.h"

int main() {
    int fd;
    struct sockaddr_in ender;
    char buffer[_BUFF_TAM];
    
    //Configurando socket
    if(configura_socket_cliente(&fd, &ender) == -1) {
        return -1;
    }
    //Envia nome de usuário ao servidor
    envia_nome_usuario(fd);
    //Preeche o buffer com zeros, ou seja, '\0'
    memset(&buffer, '\0', _BUFF_TAM);
    //Loop do jogo
    int jogo_acabou = 0;
    char *msg;
    int opt;
    while(!jogo_acabou) {
        msg = recebe_UI(fd);
        if(msg[0] == '*') {
            system("clear");
        } else if(msg[0] == '%') {
            scanf("%d", &opt);
            envia_OPT(fd, opt);
        } else if(msg[0] == 'I') {
            scanf("%c", &buffer[0]);
            envia_UI(fd, buffer);
        } else {
            printf("%s", msg);
            fflush(stdout);
        }
    }
    //Fechando descritor de arquivo do socket
    close(fd);
    return 0;
}