CC = gcc
C_FLAGS = 

MAIN = ./main
OBJ = ./obj
BIN = ./bin

INC = ./inc
SRC = ./src

SRCS = ${wildcard ${SRC}/*.c}
OBJS = ${SRCS:${SRC}/%.c=${OBJ}/%.o}
MAIN_CLIENTE = main_cliente
MAIN_SERVIDOR = main_servidor

all: \
	srcs \
	bin


srcs: \
	${OBJS}

bin: \
	${BIN}/${MAIN_CLIENTE} \
	${BIN}/${MAIN_SERVIDOR}

run_cliente:
	${BIN}/${MAIN_CLIENTE}

run_servidor2:
	${BIN}/${MAIN_SERVIDOR} 2

run_servidor4:
	${BIN}/${MAIN_SERVIDOR} 4

clean:
	rm ${OBJ}/*.o
	rm ${BIN}/*

${OBJ}/%.o : ${SRC}/%.c	${INC}/%.h
	${CC} -c ${C_FLAGS} $< -I ${INC} -o $@


${BIN}/% : ${MAIN}/%.c
	${CC} ${C_FLAGS} $< ${OBJ}/*.o -I ${INC} -o $@
