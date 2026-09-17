#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <Pila.h>
#include <Cola.h>

void imprimir(void *);
void torreH(Pila *pila);

int main(void)
{
	Pila pila = inicializarPila(-1);	
	Cola cola = inicializarCola();
    char cadena[30];
	inputCadena("\n Captura cadena: ",cadena,30);
	
	for(int i=0; cadena[i]!='\0' ; i++)
	{
		push(&pila, &cadena[i]);
		enqueue(&cola, &cadena[i]);
	}
	
		imprimirPila(pila,imprimir);
	//torreH
		torreH(&pila);
		imprimirPila(pila,imprimir);
		

	eliminarPila(&pila,NULL);
	eliminarCola(&cola,NULL);
	
	
    printf("\n FIN DE PROGRAMA \n\r");
    return 0;
}

void torreH(Pila *pila)
{
    Pila aux = inicializarPila(pila->limite);
    //mientras pila no este vacia
    while (!pilaVacia(*pila))
    {
        Nodo *pilaorigen = popN(pila);//crear nodo para pila 
        
        //sacamos valor de pila  para comparar 
        char valOrigen = *(char*)(pilaorigen->dato);

        // mover valores de aux a pila si son mayores al dato actual
        while (!pilaVacia(aux))
        {
            //extraer valor del nodo de cima de aux para comparar
            char valAux = *(char*)(aux.cima->dato);

            if (valAux > valOrigen)
            {
                // Si el de aux es mayor se pasa a pila
                pushN(pila, popN(&aux));
            }
            else
            {
                // Encontramos la posición correcta
                break;
            }
        }

        // insertar el nodo en  aux
        pushN(&aux, pilaorigen);
    }
	
    // Devuelve todo a la pila original para invertir el orden
    while (!pilaVacia(aux))
    {
        pushN(pila, popN(&aux));
    }

    printf("\n Pila ordenada con exito.\n");
}


void imprimir(void *dato)
{
	printf("%c",*(char*)dato);
}