#ifndef COLA_H
#define COLA_H


#include <stdio.h>
#include <stdlib.h>
#include <Nodo.h>

typedef struct
{	
	Nodo *inicio;
	Nodo *fin;
	size_t cant;
}Cola;

Cola *crearCola(void);
Cola inicializarCola(void);
void enqueue(Cola *cola,void *dato);
void enqueueN(Cola *cola,Nodo* nodo);
void* dequeue(Cola *cola);
Nodo* dequeueN(Cola *cola);
void imprimirCola(Cola cola,fn_imprimir imprimir);
void eliminarCola(Cola *cola,fn_free liberar);
int buscarDatoCola(Cola cola,void *dato,fn_comparar comparar);



#endif