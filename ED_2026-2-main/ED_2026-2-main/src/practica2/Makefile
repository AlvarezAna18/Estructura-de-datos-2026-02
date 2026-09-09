cflags = -Wall -Werror -std=c99 -O2
includes = -I ../iostring -I ../datastructures/nodo -I ../datastructures/lista
libs = ../../lib -liostring -lLista
source = $(wildcard *.c) 
output = ../../bin/practica2

build :
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"
run:
	$(output)
rebuild:
	$(MAKE) -C ..\iostring
	$(MAKE) -C ..\datastructures\nodo
	$(MAKE) -C ..\datastructures\lista
	gcc $(cflags) $(source) -o $(output) $(includes) -L $(libs)
	@echo "Compilo Exitosamente!!!"