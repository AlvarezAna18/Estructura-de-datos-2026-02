
#include "Pila.h"


Pila* crearPila(void)
{
	return calloc(1,sizeof(Pila));
}

Pila inicializarPila(int limite)
{
	return (Pila){.cima=NULL,.cant=0,.limite=limite};
}

int pilaLlena(Pila pila)
{
	if(pila.limite!=-1 && pila.cant == pila.limite)
		return TRUE;
	return FALSE;	
}
int pilaVacia(Pila pila)
{
	return (!pila.cima && pila.cant == 0);
}


void* peek(Pila pila)
{
	if( pilaVacia(pila) ) 
		return NULL;
	return pila.cima->dato;
}
void push(Pila *pila,void *dato)
{
	if( pilaLlena(*pila))
	{
		printf("\n Overflow");
		return;
	}
	Nodo *nuevaCima = crearNodo(dato);
	nuevaCima->sig = pila->cima;
	pila->cima = nuevaCima;
	pila->cant++;	
}

void pushN(Pila *pila,Nodo* nuevaCima)
{
	if( pilaLlena(*pila))
	{
		printf("\n Overflow");
		return;
	}
	nuevaCima->sig = pila->cima;
	pila->cima = nuevaCima;
	pila->cant++;	
}

void* pop(Pila *pila)
{
	void *dato = peek(*pila);
	if(dato)
	{
		Nodo *aux = pila->cima;
		pila->cima = aux->sig;
		pila->cant--;
		free(aux);
	}
	return dato;
}


Nodo* popN(Pila *pila)
{
	Nodo *viejaCima = pila->cima;
	if(viejaCima)
	{
		pila->cima = viejaCima->sig;
		viejaCima->sig = NULL;
		pila->cant--;
	}
	return viejaCima;
}
void imprimirPila(Pila pila,fn_imprimir imprimir)
{
	Pila pilaAux = inicializarPila(pila.limite);
	printf("\n [%lld] Pila:",pila.cant);
	while( !pilaVacia(pila) )
	{
		Nodo *aux = popN(&pila);
		printf("\n");
		imprimir( aux->dato);
		pushN(&pilaAux,aux);
	}
	while( !pilaVacia(pilaAux) )
	{
		pushN(&pila, popN(&pilaAux) );
	}
}

void eliminarPila(Pila *pila,fn_free liberar)
{	
	while( !pilaVacia(*pila) )
	{
		void *aux = pop(pila);
		if(liberar)
			liberar(aux);
	}
}
int buscarDatoPila(Pila pila,void *dato,fn_comparar comparar)
{
	return 0;
}




