#include "cliente.h"
#include "troca_de_segmento.h"

void envia_nome_usuario(int fd) {
    //Faz a leitura do nome de usuário na entrada como entrada no
    // stdin e envia para o descritor de arquivo correspondente
    // a variável fd.
    char buffer[_BUFF_TAM];
     /* Lendo nome do player e enviando para o servidor */
    memset(&buffer, '\0', _BUFF_TAM);
    printf("Digite seu nome(%d bytes): ", _BUFF_TAM);
    fgets(&buffer[0], _BUFF_TAM, stdin);
    buffer[_BUFF_TAM - 1] = '\0'; // Removendo \n
    envia_segmento(fd, &buffer[0], _BUFF_TAM);
    read(fd, buffer, _BUFF_TAM);
    printf("Servidor diz: %s\n", &buffer[0]);
    memset(buffer, '\0', _BUFF_TAM);
}