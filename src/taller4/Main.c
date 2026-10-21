#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <arbol.h>
#include <Nodo.h>
#include <Pila.h>

#define ASC 1
#define DEC 0


int *crearEntero(int);
void imprimir(void*);
int funcion_comparar(void *a, void *b);
void insertarArbolO(Arbol *arbol, void *dato);
void flipArbol(Arbol *arbol);
void* buscarArbol(Arbol *arbol, void *dato);

int main(void)
{
	// Crear árbol
	Nodoa *raiz = crearNodoa(crearEntero(6));
	raiz->izq = crearNodoa(crearEntero(2));
	raiz->izq->izq = crearNodoa(crearEntero(1));
	raiz->izq->dch = crearNodoa(crearEntero(4));
	raiz->izq->dch->izq = crearNodoa(crearEntero(3));
	raiz->izq->dch->dch = crearNodoa(crearEntero(5));

	raiz->dch = crearNodoa(crearEntero(8));	
	raiz->dch->izq = crearNodoa(crearEntero(7));
	raiz->dch->dch = crearNodoa(crearEntero(9));
	
	// Inicializar árbol
	Arbol arbol;
	arbol.raiz = raiz;
	arbol.cant = 9;
	arbol.comparar = funcion_comparar;
	arbol.orden = ASC; // Inicializamos en orden ascendente
	
	printf("\nArbol normal:");
	imprimirOrden(arbol, imprimir, ORDEN);
	
	// 1. Función insertar árbol
	int *nuevoDato = crearEntero(12);
    printf("\n\nInsertar dato 12");
    insertarArbolO(&arbol, nuevoDato);
	
	printf("\nArbol tras insercion:\n");
    imprimirOrden(arbol, imprimir, ORDEN);
	
	// 2. Flip
	flipArbol(&arbol);

	printf("\nArbol invertido (flip):");
	imprimirOrden(arbol, imprimir, ORDEN);
	
	// 3. Buscar dato
	int *datoBuscar = crearEntero(2);
    printf("\n\nBuscar dato 2");
    void *encontrado = buscarArbol(&arbol, datoBuscar);

    if (encontrado != NULL) {
        printf("\nResultado: Encontrado : %d", *(int*)encontrado);
    } else {
        printf("\nResultado: No encontrado.");
    }

    free(datoBuscar);
	
	return 0;
}


/*Implementar la función de inserción en un árbol binario ordenado
acomodando los valores la rama de la izquierda sean menores a los de la rama derecha
dada una función de comparación que es un miembro de la estructura Árbol. 
La función no debe ser recursiva.*/

void insertarArbolO( Arbol *arbol, void *dato)
{
	//primero de inicializan nodos de arbol : raiz, padre,actual
	Nodoa *actual;
	Nodoa *padre = NULL;
	Nodoa *nuevo;
	int comparacion;
	
	//Si el arbol esta vacio, el nuevo nodo es la raiz
	//comparar valor actual
	if (arbol == NULL || dato == NULL || arbol->comparar == NULL)
    return;

	//inicialzar raiz 
    actual = arbol->raiz;

	
	//comparacion = arbol->cmp(dato, actual->dato);
	//si dato es menor va izquierda
	//si dato es mayor va derecha
	while (actual != NULL)
    {
        padre = actual;

        comparacion = arbol->comparar(dato, actual->dato);

        if (comparacion == 0)
            return;
		
		if(arbol->orden == ASC){
			if(comparacion < 0)
				actual = actual -> izq;
			else 
				actual = actual -> dch;
			
		}
		
		else{ //dec
			if(comparacion > 0)
				actual = actual -> izq;
			else
				actual = actual -> dch;
		}

    }
	
	
	//insertar nuevo nodo en el arbol
	 nuevo = malloc(sizeof(Nodoa));

		if (nuevo == NULL)
			return;

		nuevo->dato = dato;
		nuevo->izq = NULL;
		nuevo->dch = NULL;

		//conectar el nodo al arbol
		if (padre == NULL)
		{
			arbol->raiz = nuevo;
		}
		
		else{
			comparacion = arbol ->comparar(dato, padre -> dato);
			if (arbol-> orden == ASC)
			{
				if(comparacion <0)
					padre -> izq = nuevo;
				else
					padre ->dch = nuevo;
			}
			else
			{
				if(comparacion >0)
					padre -> izq = nuevo;
				else 
					padre -> dch = nuevo;
			}
		}
		
		arbol -> cant++;

}

/*Implementar una función que invierta (flip) todas la ramas de un árbol binario ordenado
si en la rama izquierda están los valores menores a una raíz y en la derecha los mayores, 
que ahora en la rama izquierda están los mayores a la raíz y en la derecha los menores. 
*/
void flipArbol( Arbol *arbol)
{
	//inicializamos pila para recorrer
	Nodoa **pila;
    Nodoa *actual;
    Nodoa *aux;
    size_t tope = 0;

    if(arbol == NULL || arbol->raiz == NULL)
	{
        return;
	}
	
	//inicializa pila
	arbol -> orden = !arbol -> orden; //cambiar orden al contrario
	
    pila = malloc(arbol->cant * sizeof(Nodoa *));

    if (pila == NULL)
        return;

    pila[tope++] = arbol->raiz;

	//recorrer mientras tope sea mayor a 0
	//mientras haya nodos pendeintes
    while (tope > 0)
    {
		
        actual = pila[--tope];//saacr el ultimo nodo guardado
		
		//revisar desde padre
        aux = actual->izq;
        actual->izq = actual->dch;//intercambiar de izq a dch
        actual->dch = aux;

		//guardar hijos para intercambiar
        if (actual->izq != NULL)
            pila[tope++] = actual->izq;

        if (actual->dch != NULL)
            pila[tope++] = actual->dch;
    }

	//liberar pila
    free(pila);
	
}

/*Implementar una función que busca un valor dentro de un árbol binario ordenado 
utilizando la función de comparación y retorna el valor si lo encuentra, 
caso contrario, NULL. La función no debe ser recursiva.*/

void* buscarArbol( Arbol *arbol, void *dato)
{
	//inicializar nodo aux nodo actual
	Nodoa *actual;
	int comparacion;
	
	//validar si no hay nulo
	if (arbol == NULL || dato == NULL || arbol->comparar == NULL)
    return NULL;
	
	//asignar el nodo act a raiz
	actual = arbol->raiz;

	//comparar hasta encontrar el dato 
	while (actual != NULL)
    {
        comparacion = arbol->comparar(dato, actual->dato);

        if (comparacion == 0)
            return actual->dato;//si se encontro actualizar dato
		
		if(arbol -> orden == ASC)//asc
		{
			if(comparacion < 0)
				actual = actual -> izq;
			else
				actual = actual ->dch;
		}
		
		else//dec
		{
			if(comparacion > 0)
				actual = actual ->izq;
			else
				actual = actual -> dch;
			
		}
    }

    return NULL;//si no encuentra regresa nulo
} 

//auxiliares para enteros
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

int comparar(void *a, void *b) 
{
    int valA = *(int *)a;
    int valB = *(int *)b;
    return valA - valB;
}