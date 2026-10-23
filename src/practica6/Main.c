#include <stdio.h>
#include <stdlib.h>
#include "practica6.h"

int main(void) {
    Arbol arbol;
    arbol.raiz = NULL;
    
    int opcion;
    char expresion[100];
    char ch;

    do {
        printf("\n\n Expresion :)");
        printf("\n1. Capturar expresion");
        printf("\n2. Imprimir arbol de expresion");
        printf("\n3. Evaluar expresion, mostrar resultado");
        printf("\n4. Salir");
        printf("\nOpcion: ");
        scanf("%d", &opcion);

        while ((ch = getchar()) != '\n' && ch != EOF);

        switch (opcion) 
        {
            case 1:
                printf("\n ingresa expresion: ");
                fgets(expresion, sizeof(expresion), stdin);
                
                arbol.raiz = crearArbolDesdeInfix(expresion);
                printf("\nexpresion guardada y Arbol construido con exito.\n");
                break;

            case 2:
                if (!arbol.raiz) {
                    printf("\n	primero debe capturar una expresion.");
                } else {
                    printf("\n	arbol de Expresion:\n");
                    imprimirArbol(arbol, imprimirChar);
                }
                break;

            case 3:
                if (!arbol.raiz) {
                    printf("\nprimero debe capturar una expresion.");
                } else {
                    capturarValores();
                    float res = evaluarArbol(arbol.raiz);
                    printf("\nresultado  %f\n", res);
                }
                break;

            case 4:
                liberarArbol(&arbol);
                printf("\n\n baiiii \n");
                break;

            default:
                printf("\nOpcion invalida.");
        }
    } while (opcion != 4);

    return 0;
}