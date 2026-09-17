#ifndef PILA_H
#define PILA_H

#include <stdio.h>
#include <stdlib.h>
#include <Nodo.h>

typedef struct
{	
	Nodo *cima;
	size_t cant;
	size_t limite;
}Pila;

Pila *crearPila(void);
Pila inicializarPila(int);
int pilaLlena(Pila);
int pilaVacia(Pila);
void* peek(Pila pila);
void push(Pila *pila,void *dato);
void pushN(Pila *pila,Nodo* nodo);
void* pop(Pila *pila);
Nodo* popN(Pila *pila);
void imprimirPila(Pila pila,fn_imprimir imprimir);
void eliminarPila(Pila *pila,fn_free liberar);
int buscarDatoPila(Pila pila,void *dato,fn_comparar comparar);



#endif