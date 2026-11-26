#include "heap.h"

void insertarHeap(Heap *heap,void *dato)
{
	if( heap->cant!= 0)
	{
		//Agregar
		void **aux = NULL;
		while(!aux)
		{
			aux = realloc(heap->datos, (heap->cant+1)*sizeof(void*));
		}
		heap->datos = aux;
	}
	else
	{
		//Crear
		heap->datos = calloc(1,sizeof(void*));
	}
	heap->datos[ heap->cant++] = dato;
	//HEAPIFY
	heapify_up(heap);
}

void* removerHeap(Heap *heap)
{
	void *dato = NULL;
	if(heap->cant)
	{
		dato = heap->datos[0];
		heap->datos[0] = heap->datos[--heap->cant];		
		heap->datos = realloc(heap->datos, (heap->cant)*sizeof(void*));		
		//HEAPIFY
		heapify_down(heap);
	}	
	return dato;
}



void imprimirHeap(Heap *heap,fn_imprimir imprimir)
{
	printf("\n HEAP:");
	for(int i=0;i< heap->cant ; i++)
	{
		printf(" ");
		imprimir(heap->datos[i]);
	}
}


void intercambios(Heap *heap,Pila pila, int *arrNum)
{
	while(!pilaVacia(pila))
	{
		int padre = *(int*)pop(&pila);
		int cambio = padre;
		int izq = 2*padre+1;
		int dch = 2*padre+2;
		if( dch < heap->cant && heap->comparar(heap->datos[dch],heap->datos[cambio]) == heap->type )
			cambio = dch;
		if( heap->comparar(heap->datos[izq],heap->datos[cambio])  == heap->type)
			cambio = izq;
		if( cambio != padre)
		{
			void *aux = heap->datos[padre];
			heap->datos[padre] =  heap->datos[cambio];
			heap->datos[cambio] =  aux;
			if( cambio < heap->cant/2 )
				push(&pila,&arrNum[cambio]);
		}
	}
}


void heapify_up(Heap *heap)
{
	int *arrNum = calloc((heap->cant/2),sizeof(int));
	Pila pila = inicializarPila(-1);
	for(int i = 0; i < heap->cant/2 ; i++)
	{
		arrNum[i]=i;
		push(&pila,&arrNum[i]);
	}
	intercambios(heap,pila,arrNum);	
	free(arrNum);	
}


void heapify_down(Heap *heap)
{
	int *arrNum = calloc((heap->cant/2),sizeof(int));
	Pila pila = inicializarPila(-1);
	for(int i = 0; i < heap->cant/2 ; i++)
		arrNum[i]=i;
	push(&pila,&arrNum[0]);
	intercambios(heap,pila,arrNum);	
	free(arrNum);	
}


//funcion universal-------------------------------------------------------
// pos == -1: Revisa y reordena TODO el arbol
//pos >= 0: Ajusta el subarbol a partir de una posición específica
void heapify(Heap *heap, int posicion)
{
	if (heap == NULL || heap->cant == 0) return;

	int limite = (int)(heap->cant / 2);
	if (limite == 0) return;

	int *arrNum = calloc(limite, sizeof(int));
	if (!arrNum) return;

	// pos = -1 recorre de abajo hacia arriba todos los nodos no hoja
	if (posicion < 0)
	{
		for (int i = limite - 1; i >= 0; i--)
		{
			arrNum[i] = i;
			Pila pila = inicializarPila(-1);
			push(&pila, &arrNum[i]);
			intercambios(heap, pila, arrNum);
		}
	}
	//pos >= 0 y es un nodo no hoja, reordena a partir de esa posición
	else if (posicion < limite)
	{
		arrNum[posicion] = posicion;
		Pila pila = inicializarPila(-1);
		push(&pila, &arrNum[posicion]);
		intercambios(heap, pila, arrNum);
	}

	//LIBERAR ARREGLO AUX
	free(arrNum);
}