#include <stdio.h>
#include <stdlib.h>
#include "practica5.h"



int main(void)
{
	/*
	Arbol arbol;
    arbol.raiz = NULL;
    arbol.cant = 0;
	arbol.comparar = comparar;
    arbol.orden = ASC;
	*/
	
    int opcion;
    char ch;
	int num; 
	
	Nodoa *raiz = crearNodoa(crearEntero(8));

raiz->izq = crearNodoa(crearEntero(7));
raiz->izq->izq = crearNodoa(crearEntero(6));
raiz->izq->izq->izq = crearNodoa(crearEntero(4));
raiz->izq->izq->izq->izq = crearNodoa(crearEntero(1));
raiz->izq->izq->izq->dch = crearNodoa(crearEntero(5));

raiz->dch = crearNodoa(crearEntero(10));
raiz->dch->izq = crearNodoa(crearEntero(9));
raiz->dch->dch = crearNodoa(crearEntero(11));

Arbol arbol;
arbol.raiz = raiz;
arbol.cant = 9;
arbol.comparar = comparar;
arbol.orden = ASC;

printf("\n Altura %lld", (long long)altura(arbol));
printf("\n Altura %lld", (long long)alturaI(arbol));
printf("\n PREORDEN");
imprimirOrden(arbol, imprimir, PREORDEN);
printf("\n ORDEN");
imprimirOrden(arbol, imprimir, ORDEN);
printf("\n POSTORDEN");
imprimirOrden(arbol, imprimir, POSTORDEN);

//MENU---------------------------------------
	
	 do
    {
        // MENU
        printf("\n\n HOLIIII :) ");
        printf("\n1. Insertar en Arbol ");
        printf("\n2. Eliminar dato en Arbol");
        printf("\n3. Equilibrar el Arbol");
        printf("\n4. Mostrar Arbol");
        printf("\n5. Salir");

        printf("\nOpcion: ");
        scanf("%d", &opcion);

        while((ch = getchar()) != '\n' && ch != EOF);

        switch(opcion)
        {
        case 1:
			printf("\n Ingresa numero que deseas insertar");
			scanf("%d", &num);
			insertarArbolO(&arbol, crearEntero(num));
		break;

        case 2:
			printf("\n Ingresa numero que deseas eliminar");
			scanf("%d", &num);
			eliminarArbol(&arbol, &num);
		
        break;
		
        case 3:
			equilibrarArbol(&arbol);
			imprimirArbol(arbol,imprimir);
		
        break;
			
        case 4:
			printf("\n Arbol\n");
			imprimirArbol(arbol,imprimir);
		break;
		
        case 5:
			//funcion liberar
			liberarArbol(&arbol);
			
		    printf("\n\n FIN DE PROGRAMA :) ");
            break;
		break;
		
        default:
            printf("\nOpcion invalida.\n");
        }

    }
    while(opcion != 5);
	
    return 0;
}



