cflags = -Wall -Werror -std=c99 -O2 -c
includes = -I ../nodo -I ../lista
sourceNodo = ../nodo/Nodo.o ../lista/pila.o
source = $(wildcard *.c)
source_o = $(wildcard *.o)
output = ../../../lib/libArbol.a

build :
	gcc $(cflags) $(source) $(includes)
	-rm "$(output)"
	ar rcs $(output) $(source_o) $(sourceNodo) 
	@echo "Compilo Exitosamente!!!"
