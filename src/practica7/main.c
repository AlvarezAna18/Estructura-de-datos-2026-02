#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostring.h>
#include <Nodo.h>
#include <heap.h>
#include <arbol.h>

int *crearEntero(int num);
int compararEntero(void *pa, void *pb);
void imprimir(void *dato);
Nodoa* construirNodoArbolDesdeHeap(Heap *heap, int pos);
void vaciarHeap(Heap *heap);

int main(void)
{
	int opcion;
	char ch;
	srand((unsigned int)time(NULL));

	Heap heap = {NULL, 0, HEAPMIN, compararEntero}; //inicializar en heap min


	// Inicialización con la secuencia exacta de la imagen
	int valoresIniciales[] = {11, 15, 12, 16, 17, 14, 13};
	int totalIniciales = sizeof(valoresIniciales) / sizeof(valoresIniciales[0]);

	//guardar valores de prueba de profe
	for (int i = 0; i < totalIniciales; i++)
	{
		insertarHeap(&heap, crearEntero(valoresIniciales[i]));
	}
	
	//menu
	do
	{
		// MENU
		printf("\n\n Bienvenido :) ");
		printf("\n [0] CAMBIAR PRIORIDAD ");
		printf("\n [1] MOSTRAR COLA DE IMPRESION ");
		printf("\n [2] AGREGAR ARCHIVO ");
		printf("\n [3] PROCESAR/IMPRIMIR ARCHIVO");
		printf("\n [4] ELIMINAR ARCHIVO");
		printf("\n [5] ELIMINAR TODOS LOS ARCHIVOS");
		printf("\n [6] TERMINAR PROGRAMA");

		printf("\nOpcion: ");
		if (scanf("%d", &opcion) != 1) opcion = -1;
		while((ch = getchar()) != '\n' && ch != EOF);


		switch(opcion)
		{

		//Registrar alumno
		case 0:
			{
				//invierte la prioridad de impresion, por default esta en heap minimo
				if (heap.type == HEAPMIN) 
				{
					heap.type = HEAPMAX;
					printf("\n cambio de HEAPMIN a HEAPMAX.\n");
				} 
				else 
				{
					heap.type = HEAPMIN;
					printf("\n cambio de HEAPMAX a HEAPMIN.\n");
				}
				//convertir a -1 para reordenar todo el heap 
				heapify(&heap, -1);
				break;
			}
		case 1:
			{
				//mostrar archivos de la cola de impresion en version arreglo y arbol
				printf("\n	 imprimir arreglo	");
				imprimirHeap(&heap, imprimir);
				
				printf("\n\n	 imprimir arbol	\n");
				if (heap.cant == 0) 
				{
					printf("	la cola esta vacia	\n");
				} 
				else 
				{
					//crear e imprimir arbol
					Arbol miArbol;
					miArbol.raiz = construirNodoArbolDesdeHeap(&heap, 0);
					miArbol.cant = heap.cant;
					miArbol.comparar = compararEntero;
					miArbol.orden = ASC;

					imprimirArbol(miArbol, imprimir);
				}
				break;
			}
		case 2:
			{
				//agregar un nuevo archivo con un nombre de documento y num de paguinas aleatorio
				//se agrega a la cola de impresion (utilizando heapify)
				int paginasAleatorias = (rand() % 50) + 1;
				int *nuevoEntero = crearEntero(paginasAleatorias);

				printf("\n	archivo con cant de paguinas: %d", *nuevoEntero);
				insertarHeap(&heap, nuevoEntero);
				printf("\n	agregado a la cola\n");
				break;
			}
		case 3:
			{
				//uno es el de mayor prioridad
				
				//elimina/saca un archivo en especifico 
				//muestran archivos de la cola de imprecion
				//se solicita la selccion del archivo 
				//el archivo de mayor prioridad en la cola de impresión (heap)
				//print f imprimiendo... 
				if (heap.cant == 0)//validar si no hay nada en el arreglo
				{
					printf("\n	la cola esta vacia.\n");
				}
				else
				{
					// Remueve la raiz la mayor prioridad 
					int *documentoProcesado = (int*)removerHeap(&heap);
					if (documentoProcesado != NULL)
					{
						printf("\n	Imprimiendo archivo con mayor prioridad %d paginas...  \n", *documentoProcesado);
						//liberar el nodo sacado
						free(documentoProcesado);
					}
				}
				break;
			}
		case 4:
			{
				// solo el q uno quiera
				
				//eliminar archivo especifico
				//preguntar por el archivo a eliminar
				//
				if (heap.cant == 0)
				{
					printf("\n	la cola esta vacia.\n");
				}
				else
				{
					printf("\n	Archivos actuales en la cola:\n");
					for (size_t i = 0; i < heap.cant; i++)
					{
						printf("	[%zu] %d paginas\n", i, *(int*)heap.datos[i]);
					}

					int seleccion;
					printf("\n	Ingrese el indice del archivo a eliminar: ");
					if (scanf("%d", &seleccion) == 1 && seleccion >= 0 && seleccion < (int)heap.cant)
					{
						// Liberar el entero en la posición seleccionada
						free(heap.datos[seleccion]);

						// Mover el último elemento a la posición eliminada
						heap.datos[seleccion] = heap.datos[--heap.cant];

						// Reajustar memoria
						if (heap.cant > 0)
						{
							heap.datos = realloc(heap.datos, heap.cant * sizeof(void*));
							// Reordenar la propiedad del heap
							heapify(&heap, -1);
						}
						else
						{
							free(heap.datos);
							heap.datos = NULL;
						}

						printf("\n	Archivo eliminado exitosamente!\n");
					}
					else
					{
						printf("\n	Indice invalido.\n");
					}
				}
				break;
			}
		case 5:
			{
				//vacia cola de impresion
				vaciarHeap(&heap);
				printf("\n\t Se vacio la cola de impresion \n");
				break;
			}
		case 6:
			{
				printf("\n saliendo. . .\n");
				// liberar memoria
				vaciarHeap(&heap);
				break;
			}
		default:
			printf("\nOpcion invalida.\n");
		}

	}
	while(opcion != 6);
	
	printf("\n\n FIN DE PROGRAMA\n\n");
	return 0;
}


int *crearEntero(int num)
{
	int *dato = calloc(1, sizeof(int));
	if (dato) *dato = num;
	return dato;
}

void imprimir(void *dato)
{
	if (dato) printf("%d", *(int*)dato);
}

int compararEntero(void *pa, void *pb)
{
	int a = *(int*)pa;
	int b = *(int*)pb;
	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}

// Convierte el arreglo del Heap a la estructura de nodos binarios (Nodoa) de tu arbol.h
Nodoa* construirNodoArbolDesdeHeap(Heap *heap, int pos)
{
	if (pos >= (int)heap->cant) return NULL;

	Nodoa *nodo = crearNodoa(heap->datos[pos]);
	if (nodo)
	{
		nodo->izq = construirNodoArbolDesdeHeap(heap, 2 * pos + 1);
		nodo->dch = construirNodoArbolDesdeHeap(heap, 2 * pos + 2);
	}

	return nodo;
}

//liberar 
void vaciarHeap(Heap *heap)
{
	if (heap == NULL || heap->datos == NULL) return;

	for (size_t i = 0; i < heap->cant; i++)
	{
		free(heap->datos[i]);
	}
	free(heap->datos);
	heap->datos = NULL;
	heap->cant = 0;
}