cflags = -Wall -Werror -std=c99 -O2 -c
includes = -I ../nodo -I ../lista -I ../arbol
sourceNodo = ../nodo/Nodo.o ../lista/pila.o ../arbol/arbol.o
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libHeap.a

build :
	gcc $(cflags) $(source) $(includes)
	-rm "$(output)"
	ar rcs $(output) $(source_o) $(sourceNodo) 
	@echo "Compilo Exitosamente!!!"
