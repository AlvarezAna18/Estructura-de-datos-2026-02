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
	make -C ..\iostring
	make -C ..\datastructures\nodo
	make -C ..\datastructures\lista
	make -C ..\datastructures\arbol
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"