LIBS=-lncurses
CFLAGS=-O2 -pedantic -Wall

nc: main.c
	gcc ${CFLAGS} ${LIBS} -o $@ $^
