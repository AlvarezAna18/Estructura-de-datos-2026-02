#ifndef PRACTICA5_H
#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <arbol.h>
#include <Nodo.h>


int *crearEntero(int);
void imprimir(void*);
void eliminarArbol(Arbol *arbol, void *dato);
void liberarArbol(Arbol *arbol);
void equilibrarArbol(Arbol *arbol);

#endif