#include "Cola.h"

Cola *crearCola(void)
{
	return (Cola*)calloc(1,sizeof(Cola));
}

Cola inicializarCola(void)
{
	return (Cola){.inicio=NULL,.fin=NULL,.cant=0};
}

void enqueue(Cola *cola,void *dato)
{
	Nodo *nuevoFin = crearNodo(dato);
	if(!cola->fin)
		cola->inicio = cola->fin = nuevoFin;
	else
	{
		cola->fin->sig = nuevoFin;
		cola->fin = nuevoFin;
	}
	cola->cant++;
}

void enqueueN(Cola *cola,Nodo* nuevoFin)
{
	if(!cola->fin)
		cola->inicio = cola->fin = nuevoFin;
	else
	{
		cola->fin->sig = nuevoFin;
		cola->fin = nuevoFin;
	}
	cola->cant++;	
}

void* dequeue(Cola *cola)
{
	if(!cola->inicio)
		return NULL;
	Nodo *viejoInicio = cola->inicio;
	void *dato = viejoInicio->dato;	
	cola->inicio = viejoInicio->sig;	
	free(viejoInicio);
	if(!cola->inicio)
		cola->fin = NULL;
	cola->cant--;
	return dato;	
}

Nodo* dequeueN(Cola *cola)
{
	Nodo *viejoInicio = cola->inicio;
	if(!viejoInicio)
		return NULL;
	cola->inicio = viejoInicio->sig;
	viejoInicio->sig = NULL;
	if(!cola->inicio)
		cola->fin = NULL;
	cola->cant--;
	return viejoInicio;	
}

void imprimirCola(Cola cola,fn_imprimir imprimir)
{
	printf("\n [%lld] Cola: ",cola.cant);
	for(int i = 0; i < cola.cant ; i++)
	{
		Nodo *viejoInicio = dequeueN(&cola);
		imprimir(viejoInicio->dato);
		enqueueN(&cola,viejoInicio);
	}
}

void eliminarCola(Cola *cola,fn_free liberar)
{
	while(cola->inicio)
	{
		void *aux = dequeue(cola);
		if(liberar)
			liberar(aux);
	}
}

int buscarDatoCola(Cola cola,void *dato,fn_comparar comparar)
{
	return 0;
}