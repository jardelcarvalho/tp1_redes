#include "troca_de_segmento.h"
#include "truco.h"

void envia_segmento(int fd, char *buffer, int tam_buffer) {
    //Envia os bytes presentes no buffer e após isso
    // preenche os bytes no alcance da variável tam_buffer com
    // o caractere '\0'.
    send(fd, buffer, tam_buffer, 0);
    memset(buffer, '\0', tam_buffer);
}

void recebe_segmento(int fd, char *buffer, int tam_buffer) {
    //Lê segmento presente no descritor de arquivo para
    // o buffer. O número de caracteres lidos é determinado
    // pela variável tam_buffer.
    //Antes de realizar a leitura é feito o zeramento do buffer.
    memset(buffer, '\0', tam_buffer);
    read(fd, buffer, tam_buffer);
}