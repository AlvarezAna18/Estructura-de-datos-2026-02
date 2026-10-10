#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <arbol.h>
#include <Nodo.h>

int *crearEntero(int);
void imprimir(void*);


int main(void)
{
	Nodoa *raiz = crearNodoa( crearEntero(4) );
	raiz->izq = crearNodoa(crearEntero(2) );
	raiz->izq->izq = crearNodoa(crearEntero(1) );
	raiz->izq->dch = crearNodoa(crearEntero(3) );
	raiz->dch =  crearNodoa(crearEntero(6) );	
	raiz->dch->izq =  crearNodoa(crearEntero(5) );
	raiz->dch->dch = crearNodoa(crearEntero(7) );
	Arbol arbol;
	arbol.raiz = raiz;
	printf("\n Altura %d", altura(arbol));
	printf("\n Altura %d", alturaI(arbol));
	printf("\n PREORDEN");
	imprimirOrden(arbol,imprimir,PREORDEN);
	printf("\n ORDEN");
	imprimirOrden(arbol,imprimir,ORDEN);
	printf("\n POSTORDEN");
	imprimirOrden(arbol,imprimir,POSTORDEN);
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}


int *crearEntero(int num)
{
	int *dato = calloc(1,sizeof(int));
	*dato = num;
	return dato;
}
void imprimir(void *dato)
{
	printf("%d",*(int*)dato);
}