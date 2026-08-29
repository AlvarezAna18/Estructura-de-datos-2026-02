#include "Nodo.h"

Nodo* crearNodo(void *dato)
{
	Nodo *nuevo = calloc(1,sizeof(Nodo));
	nuevo->dato = dato;
	return nuevo;
}

void swapNodo(Nodo *a,Nodo *b)
{
	void *aux = a->dato;
	a->dato = b->dato;
	b->dato = aux;
}