#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <Pila.h>
#include <Cola.h>
#include "Cancion.h"

int main(void)
{
    int option, corre_programa;
    corre_programa = 1;
    
    while(corre_programa)
    {
        // Inicializamos las estructuras dentro del ciclo para cada iteración limpia
        Pila pila = inicializarPila(-1);	
        Cola cola = inicializarCola();
        
        printf("\n\r Practica 3 ");
        printf("\n\r");
        printf("\n\r [0] Palindromo");
        printf("\n\r [1] Verificacion de parentesis");
        printf("\n\r [2] Salir");
        printf("\n\r Escoge opcion: ");
        scanf("%d", &option);
        clear_buffer();
        
        switch(option)
        {
            case 0:
                capturaCadena(&pila, &cola);
                printf("\n Pila antes de procesar: ");
                imprimirPila(pila, imprimir);
                printf("\n");

                palindromo(&pila, &cola);
                printf(" Pila despues de procesar: ");
                imprimirPila(pila, imprimir);
                printf("\n");
                
                break;
                
            case 1:
                capturaCadena(&pila, &cola);
                printf("\n Pila antes de procesar: ");
                imprimirPila(pila, imprimir);
                printf("\n");

                parentesis(&pila);
                printf(" Pila despues de procesar: ");
                imprimirPila(pila, imprimir);
                printf("\n");
                
                break;
                
            case 2:
                corre_programa = 0;
                break;
            
            default:
                printf("\n Opcion no valida.\n");
                break;
        }
        
        // Limpiar memoria al terminar cada opción del menú
        eliminarPila(&pila, NULL);
        eliminarCola(&cola, NULL);
    }
    
    printf("\n FIN DE PROGRAMA \n\r");
    return 0;
}