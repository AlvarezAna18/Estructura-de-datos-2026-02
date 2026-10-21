#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <arbol.h>
#include <Nodo.h>

int *crearEntero(int);
void imprimir(void*);
void eliminarArbol(Arbol *arbol, void *dato);
void liberarArbol(Arbol *arbol);
void equilibrarArbol(Arbol *arbol);



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


void equilibrarArbol(Arbol *arbol)
{
    if (arbol == NULL || arbol->raiz == NULL || arbol->cant <= 1)
        return;

    //reservar arreglo
    void **arr = malloc(arbol->cant * sizeof(void*));
    if (arr == NULL) return;

    Pila pila = inicializarPila(-1);
    Nodoa *actual = arbol->raiz;
    int idx = 0;

    //recorrido Inorden guardar los datos ordenados
    while (actual != NULL || !pilaVacia(pila)) {
        while (actual != NULL) {
            push(&pila, actual);
            actual = actual->izq;
        }
        actual = pop(&pila);
        arr[idx++] = actual->dato;
        actual = actual->dch;
    }

    int totalElementos = idx;

    //liberar nodos en postorden
    pila = inicializarPila(-1);
    actual = arbol->raiz;
    Nodoa *ultimo_visitado = NULL;

    while (actual != NULL || !pilaVacia(pila)) 
	{
        if (actual != NULL) 
			{
				push(&pila, actual);
				actual = actual->izq;
			} 
		else 
		{
            Nodoa *nodoTope = peek(pila);
            if (nodoTope->dch != NULL && ultimo_visitado != nodoTope->dch) 
				{
					actual = nodoTope->dch;
				} 
			else 
				{
					ultimo_visitado = pop(&pila);
					free(ultimo_visitado);
				}
        }
    }

    //reiniciar arbol
    arbol->raiz = NULL;
    arbol->cant = 0;
    arbol->orden = ASC;

    //reservar memoria para pilas
    int *pilaInicio = malloc(totalElementos * sizeof(int));
    int *pilaFin = malloc(totalElementos * sizeof(int));
    void **arrInsercion = malloc(totalElementos * sizeof(void*)); //guarda el orden exacto

    if (pilaInicio == NULL || pilaFin == NULL || arrInsercion == NULL) {
        free(pilaInicio);
        free(pilaFin);
        free(arrInsercion);
        free(arr);
        return;
    }

    int tope = 0;
    int idxInsercion = 0;

    pilaInicio[tope] = 0;
    pilaFin[tope] = totalElementos - 1;
    tope++;

    //reconstrucción con pilas
    while (tope > 0)
    {
        tope--;
        int ini = pilaInicio[tope];
        int fin = pilaFin[tope];

        if (ini > fin) continue;

        //operacion para redondear para arriba
        int medio = ini + (fin - ini + 1) / 2;

        //guarar en el arreglo
        arrInsercion[idxInsercion++] = arr[medio];
		
		//inserta en arbol
        insertarArbolO(arbol, arr[medio]);

        //dch a la pila
        if (medio + 1 <= fin) {
            pilaInicio[tope] = medio + 1;
            pilaFin[tope] = fin;
            tope++;
        }

        //izq a la pila
        if (ini <= medio - 1) {
            pilaInicio[tope] = ini;
            pilaFin[tope] = medio - 1;
            tope++;
        }
    }

    //arreglo final
    printf("\nArreglo de insercion generado: [ ");
    for (int i = 0; i < totalElementos; i++) {
        printf("%d", *(int*)arrInsercion[i]);
        if (i < totalElementos - 1) {
            printf(", ");
        }
    }
    printf(" ]\n\n");

    //liberar memoria que use de aux
    free(pilaInicio);
    free(pilaFin);
    free(arrInsercion);
    free(arr);
}


void eliminarArbol(Arbol *arbol, void *dato)
{
    if (arbol == NULL || arbol->raiz == NULL || arbol->comparar == NULL)
        return;

    Nodoa *actual = arbol->raiz;
    Nodoa *padre = NULL;
    int comparacion;
    int encontrado = 0;

    //buscar el nodo y su padre de manera iterativa
    while (actual != NULL)
    {
        comparacion = arbol->comparar(dato, actual->dato);
        if (comparacion == 0)
        {
            encontrado = 1;
            break;
        }
        padre = actual;
        if (arbol->orden == ASC)
        {
            if (comparacion < 0) actual = actual->izq;
            else actual = actual->dch;
        }
        else
        {
            if (comparacion > 0) actual = actual->izq;
            else actual = actual->dch;
        }
    }

    if (!encontrado)
    {
        printf("\nElemento no encontrado en el arbol.");
        return;
    }

    //el nodo tiene 0 o 1 hijo
    if (actual->izq == NULL || actual->dch == NULL)
    {
        Nodoa *hijo = (actual->izq != NULL) ? actual->izq : actual->dch;

        if (padre == NULL)
        {
            arbol->raiz = hijo;
        }
        else if (padre->izq == actual)
        {
            padre->izq = hijo;
        }
        else
        {
            padre->dch = hijo;
        }

        free(actual->dato);
        free(actual);
    }
    else
    {
        //el nodo tiene 2 hijos 
        Nodoa *sucesorPadre = actual;
        Nodoa *sucesor = actual->dch;

        while (sucesor->izq != NULL)
        {
            sucesorPadre = sucesor;
            sucesor = sucesor->izq;
        }

        //intercambiar datos
        void *aux = actual->dato;
        actual->dato = sucesor->dato;
        sucesor->dato = aux;

        //desvincular el sucesor
        Nodoa *hijoSucesor = sucesor->dch;
        if (sucesorPadre->izq == sucesor)
        {
            sucesorPadre->izq = hijoSucesor;
        }
        else
        {
            sucesorPadre->dch = hijoSucesor;
        }

        free(sucesor->dato);
        free(sucesor);
    }

    arbol->cant--;
    printf("\nElemento eliminado exitosamente.");
}


//liberar arbol
void liberarArbol(Arbol *arbol)
{
    if (arbol == NULL || arbol->raiz == NULL)
        return;

    Pila pila = inicializarPila(-1);
    Nodoa *actual = arbol->raiz;
    Nodoa *ultimo_visitado = NULL;

    while (actual != NULL || !pilaVacia(pila))
    {
        if (actual != NULL)
        {
            push(&pila, actual);
            actual = actual->izq;
        }
        else
        {
            Nodoa *padre = peek(pila);			
            if (padre->dch != NULL && ultimo_visitado != padre->dch)
            {
                actual = padre->dch;
            }
            else
            {
                ultimo_visitado = pop(&pila);
                
                //liberar en postorden hijo y luego raiz
				//libera el entero 
                free(ultimo_visitado->dato);
				
				//libera nodo
                free(ultimo_visitado);       
            }
        }
    }

    arbol->raiz = NULL;
    arbol->cant = 0;
}


