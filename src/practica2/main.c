#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <ListaD.h>
#include "Cancion.h"
int main(void)
{
	int option,corre_programa, bucle;
	ListaD lista = inicializarListaD();
	Canciones canciones = cargarCanciones();
	Nodod *actual = NULL; 
	corre_programa = 1;
	bucle = 0;
	while(corre_programa)
	{
		printf("\n\r Crea tu playlist ----------------------------------------------------------------");
		printf("\n\r");
		printf("\n\r [0] BUCLE");
		printf("\n\r [1] ANTERIOR");
		printf("\n\r [2] SIGUIENTE");
		printf("\n\r [3] AGREGAR CANCION");
		printf("\n\r [4] MOSTRAR LISTA DE REPRODUCCION");
		printf("\n\r [5] QUITAR CANCION");
		printf("\n\r [6] REINICIAR REPRODUCCION");
		printf("\n\r [7] TERMINAR PROGRAMA");
		printf("\n\r Escoge opcion: ");
		scanf("%d",&option);
		clear_buffer();
		switch(option)
		{
			case 0:
				//si no es lista circular se crea
				 bucle = !bucle;

				if (bucle)
					printf("\nModo bucle activado :)\n");
				else
					printf("\nModo bucle desactivado :( \n");

				break;
				
			case 1:
				anterior(lista, &actual, bucle);
				imprimirReproductor(actual, lista, bucle);
				break;

			case 2:
				siguiente(lista, &actual, bucle);
				imprimirReproductor(actual, lista, bucle);
				break;
				
			case 3:
				//SE MUESTRA UN MENU CON LAS CANCIONES DISPONIBLES
				imprimirCanciones(canciones);
				//SE SELECCIONA LA CANCION
				printf("\n\r Selecciona una cancion: ");
				int idx_cancion;
				scanf("%d",&idx_cancion);
				clear_buffer();
				
				if(idx_cancion < 0 || idx_cancion >= (int)canciones.cant)
					{
					printf("\n\r Opcion invalida");
					break;
					}
				//SE MUESTRA LA LISTA DE REPRODUCCION
				printf("\n\r Lista de reproduccion actual:");
				imprimirListaIFD(lista, imprimirNombre);
				//SE SELECCIONA EN QUE POSICION DE LA COLA SE AGREGARA
				printf("\n\r Posicion para agregar (0 a %zu): ",lista.cant);
				int pos;
				scanf("%d",&pos);
				clear_buffer();
				
				if(pos < 0 || pos > (int)lista.cant)
					{
						printf("\n\r Posicion invalida");
						break;
					}
				
				//SE AGREGA LA CANCION A LA COLA RESPETANDO LA POSICION ELEGIDA
				insertarPosicionD(&lista, &canciones.cancion[idx_cancion], pos);
			
				//si no habia ninguna cancion reproduciendose, la recien agregada pasa a ser la actual
				if(!actual)
					actual = lista.inicio;
				break;
			
			case 4:
			//SE MUESTRA LA COLA DE REPRODUCCION
			//se muestra lista imprimirlistaifd
			imprimirListaIFD(lista, imprimirCancion);
			break;
			
			case 5:
				if(lista.cant == 0)
				{
					printf("\n\r La lista de reproduccion esta vacia");
					break;
				}
			//SE MUESTRA UN MENU CON LAS CANCIONES DE LA COLA DE REPRODUCCION
			printf("\n\r Lista de reproduccion:");
			int i = 0;
			
			Nodod *aux = lista.inicio;
			do
				{
				printf("\n\r[%d] ",i);
				imprimirNombre(aux->dato);
				aux = aux->sig;
				i++;
				}while(aux && aux != lista.inicio);
				//SE SELECCIONA UNA OPCION Y SE ELIMINA
				printf("\n\r Cual quitar: ");
				int pos_quitar;
				scanf("%d",&pos_quitar);
				clear_buffer();
				
				if(pos_quitar < 0 || pos_quitar >= (int)lista.cant)
				{
					printf("\n\r Opcion invalida");
					break;
				}
				
				Nodod *nodo = obtenerNodoD(lista, pos_quitar);
				//si el usuario elimina la cancion que esta reproduciendo actualmente, la nueva actual sera la siguiente
				if(nodo == actual)
				{
					if(actual->sig && actual->sig != actual)
					actual = actual->sig;
					else if(actual->ant && actual->ant != actual)
					actual = actual->ant;
					else
					actual = NULL;
				}
			//funcion quitar dato LISTAD
			eliminarNodoD(&lista, nodo, NULL);
			break;
			
			case 6:
			//mostrar inicio lista de reproduccion
			actual = lista.inicio;
			break;
			
			case 7:
				corre_programa=0;
				break;
			
			default:
			break;
		}
	}
	
	printf("\n FIN DE PROGRAMA \n\r");
	return 0;
}