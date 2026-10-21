#include <stdio.h>
#include <stdlib.h>
#include "practica6.h"



int main(void)
{
	Arbol arbol;
    arbol.raiz = NULL;
    arbol.cant = 0;
	arbol.comparar = comparar;
    arbol.orden = ASC;
	
    int opcion;
    char ch;
	char expresion[];

//MENU---------------------------------------
	
	 do
    {
        // MENU
        printf("\n\n Expresion :)  ");
        printf("\n1. Capturar expresion");
        printf("\n2. Imprimir arbol de expresion");
        printf("\n3. Evaluar exoresion, mostrar resultado");
        printf("\n4. Salir");

        printf("\nOpcion: ");
        scanf("%d", &opcion);

        while((ch = getchar()) != '\n' && ch != EOF);

        switch(opcion)
        {
        case 1:
			printf("\n captura arreglo la expresion a evaluar");
		break;

        case 2:
			printf("\n Arbol de expresion:");
			imprimirArbol(arbol,imprimir);	
		
        break;
		
        case 3:	
			printf("\n Mostrar resultado de expresion");
			evaluarArbol(&arbol);
        break;
			
        case 4:
		//funcion liberar
			liberarArbol(&arbol);
		    printf("\n\n FIN DE PROGRAMA :) ");
		break;
		
        default:
            printf("\nOpcion invalida.\n");
        }

    }
    while(opcion != 4);
	
    return 0;
}



