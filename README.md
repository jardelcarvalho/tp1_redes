# tp1_redes

# Documentação:
#    A documentação se encontra no diretório /doc.

## Dependências:
  ### GCC 7.3.0
  
  ### GNU Make 4.1


# Diretivas para compilação:

### (1) Navegue pelo terminal até o diretório onde se encontra o arquivo Makefile do projeto

### (2) Digite "make" sem aspas no terminal


# Diretivas para execução:

## (1) Navegue pelo terminal até o diretório onde se encontra o arquivo Makefile do projeto

## -- Servidor
    Para executar o programa que consiste no funcionamento do servidor digite "make run_servidor2" ou "make run_servidor4", ambos comandos sem as aspas.
    "make run_servidor2" consiste na execução de um servidor que oferece suporte para o game de truco com 2 jogadores
    "make run_servidor4" consiste na execução de um servidor que oferece suporte para o game de truco com 4 jogadores

## -- Cliente (Jogador)
    Com relação aos clientes que são os correspondentes players do game, é necessário que se abra um terminal para cada cliente que jogará o game, ou seja:
    Se foi executado um servidor com suporte para 2 jogadores, devem então ser abertos 2 terminais adicionais além do terminal do servidor.
    Se foi executado um servidor com suporte para 4 jogadores, devem então ser abertos 4 terminais adicionais além do terminal do servidor.
    Feito isso, em cada um dos terminais abertos para os clientes, navegue até o diretório onde se encontra o arquivo Makefile do projeto e então digite
        em cada terminal cliente o seguinte comando sem as aspas "make run_cliente". Desta forma o cliente entrará na fila de aceitação do servidor.
    Após ser aceito pelo servidor o jogador deve inserir o seu nome e aguardar o(s) adversários realizarem o mesmo procedimento para então, em sequência,
        ser dado o início ao jogo de Truco.

# Diretivas para apagar binários gerados pela compilação:
    Navegue pelo terminal até o diretório onde se encontra o arquivo Makefile e digite sem aspas o comando "make clean".