cflags = -Wall -Werror -std=c99 -O2 -c
includes = -I ../nodo
sourceNodo = ../nodo/Nodo.o
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libLista.a

build :
	gcc $(cflags) $(source) $(includes)
	ar rcs $(output) $(source_o) $(sourceNodo) 
	@echo "Compilo Exitosamente!!!"
