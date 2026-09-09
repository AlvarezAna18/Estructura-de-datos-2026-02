#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <Nodo.h>

typedef struct
{
	Nodo *inicio;
	Nodo *fin;
	size_t cant;
	Orden orden;
	fn_comparar comparar;
}Lista;

Lista inicializarLista(void);
void insertarOrdenado(Lista *lista,void *dato);
void imprimirLista(Lista lista,fn_imprimir imprimir);
void eliminarLista(Lista *lista,fn_free liberar);
void insertarFinal(Lista *lista,void *dato);
void eliminarDato(Lista *lista,void *dato,fn_comparar comparar);
int buscarDato(Lista lista,void *dato,fn_comparar comparar);
void ordenarLista(Lista *lista,fn_comparar comparar,Orden orden);


#endif