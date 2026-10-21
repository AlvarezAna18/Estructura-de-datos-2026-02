cflags = -Wall -Werror -std=c99 -O2
includes = -I ../iostring -I ../datastructures/nodo -I ../datastructures/lista -I ../datastructures/arbol
libs = ../../lib -liostring -lArbol
source = $(wildcard *.c) 
output = ../../bin/practica5

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run:
	$(output)
rebuild:
	$(MAKE) -C ../iostring
	$(MAKE) -C ../datastructures/nodo
	$(MAKE) -C ../datastructures/lista
	$(MAKE) -C ../datastructures/arbol
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"