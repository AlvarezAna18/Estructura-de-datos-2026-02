#include "arbol.h"


size_t altura(Arbol arbol)
{
	Arbol arbol_izq,arbol_dch;
	size_t hd,hi;
	if(!arbol.raiz) 
		return 0;
	if(!arbol.raiz->izq && !arbol.raiz->dch)
		return 1;
	arbol_izq.raiz = arbol.raiz->izq;
	arbol_dch.raiz = arbol.raiz->dch;
	hi = altura(arbol_izq);
	hd = altura(arbol_dch);
	if( hi>hd )
		return hi + 1;
	else
		return hd + 1;
}




size_t alturaI(Arbol arbol)
{
	size_t max_altura = 0;
	
	if (!arbol.raiz)
		return max_altura;

	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			//SE RECORREN LOS HIJOS IZQUIERDOS
			// Apilar nodo padre antes del bajar
			push(&pila, actual);
			
			// Actualizar la altura máxima según la profundidad de la pila
			if (pila.cant > max_altura)
				max_altura = pila.cant;
			
			actual = actual->izq;
		}
		else
		{
			//Se consulta el padre
			Nodoa *padre = peek(pila);
			
			// Si existe hijo derecho y aún no lo hemos visitado, recorrer
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
			{
				actual = padre->dch;
			}
			else
			{
				// Remover si ya se recorrieron los hijos
				ultimo_visitado = pop(&pila);
			}
		}
	}

	return max_altura;
}


void preordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
	Nodoa *ultimo_visitado = NULL;

	while (actual != NULL || !pilaVacia(pila))
	{
		if (actual != NULL)
		{
			printf(" ");
			imprimir(actual->dato);
			push(&pila, actual);
			actual = actual->izq;
		}
		else
		{
			Nodoa *padre = peek(pila);			
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = pop(&pila);
		}
	}
}


void ordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
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
			Nodoa *padre = pop(&pila);			
			printf(" ");
			imprimir(padre->dato);
			if (padre->dch != NULL && ultimo_visitado != padre->dch)
				actual = padre->dch;
			else
				ultimo_visitado = padre;
		}
	}
}



void postordenI(Arbol arbol,fn_imprimir imprimir)
{
	if (!arbol.raiz)
		return ;
	Pila pila = inicializarPila(-1);
	Nodoa *actual = arbol.raiz;
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
				actual = padre->dch;
			else
			{
				printf(" ");
				imprimir(padre->dato);
				ultimo_visitado = pop(&pila);
			}
		}
	}
}


void preorden(Nodoa *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	printf(" ");
	imprimir(raiz->dato);
	preorden(raiz->izq,imprimir);
	preorden(raiz->dch,imprimir);
}

void orden(Nodoa *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	orden(raiz->izq,imprimir);
	printf(" ");
	imprimir(raiz->dato);
	orden(raiz->dch,imprimir);	
}


void inverso(Nodoa *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	inverso(raiz->dch,imprimir);	
	printf(" ");
	imprimir(raiz->dato);
	inverso(raiz->izq,imprimir);
}

void postorden(Nodoa *raiz,void (*imprimir)(void*))
{
	if(!raiz)
		return;
	postorden(raiz->izq,imprimir);
	postorden(raiz->dch,imprimir);
	printf(" ");
	imprimir(raiz->dato);	
}


void imprimirOrden(Arbol arbol,fn_imprimir imprimir,int opcion)
{
	switch(opcion)
	{
		case PREORDEN: 
			//preorden(arbol.raiz,imprimir);
			preordenI(arbol,imprimir);
			break;
		case ORDEN: 
			//orden(arbol.raiz,imprimir);
			ordenI(arbol,imprimir);
			break;
		case INVERSO: 
			inverso(arbol.raiz,imprimir);
			break;
		case POSTORDEN: 
			//postorden(arbol.raiz,imprimir);			
			postordenI(arbol,imprimir);
			break;
	}
}




void imprimir_arbol(Nodoa* nodo, int nivel,fn_imprimir imprimir)
{
    int i;
    if (nodo != NULL)
        {
        printf(" ");
		imprimir(nodo->dato);
        if(nodo->dch)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____R ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->dch, nivel + 1,imprimir);
        }
        if(nodo->izq)
        {
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                printf(" |      ");
                //printf(" |      ");
            }
            printf("\n");
            for (i = 0; i < nivel+1; i++)
            {
                if(i==nivel)
                    printf(" |____L ");
                else
                    printf(" |      ");
            }
            imprimir_arbol(nodo->izq, nivel + 1,imprimir);
        }
    }
}

void imprimirArbol(Arbol arbol,fn_imprimir imprimir)
{
	imprimir_arbol(arbol.raiz,0,imprimir);
}


//al insertar despued de eliminar arbol no se acomoda en orden
void insertarArbolO(Arbol *arbol, void *dato)
{
    if (arbol == NULL || dato == NULL || arbol->comparar == NULL)
        return;

    // Si el árbol está vacío, el nuevo nodo es la raíz
    if (arbol->raiz == NULL)
    {
        arbol->raiz = crearNodoa(dato);
        arbol->cant++;
        return;
    }

    Nodoa *actual = arbol->raiz;
    Nodoa *padre = NULL;
	int comparacion = 0;

    // Recorrer para encontrar la posición correcta
    while (actual != NULL)
    {
        padre = actual;
        comparacion = arbol->comparar(dato, actual->dato);

        if (comparacion == 0)
            return;
			int irIzquierda = (arbol->orden == ASC) ? (comparacion < 0) : (comparacion > 0);

			if (irIzquierda)
				actual = actual->izq;
			else
				actual = actual->dch;
		}

		Nodoa *nuevo = crearNodoa(dato);
		if (nuevo == NULL)
			return;

		// Recalculamos la dirección respecto al padre final encontrado
		comparacion = arbol->comparar(dato, padre->dato);
		int conectarIzquierda = (arbol->orden == ASC) ? (comparacion < 0) : (comparacion > 0);

		if (conectarIzquierda)
			padre->izq = nuevo;
		else
			padre->dch = nuevo;

		arbol->cant++;
}

int comparar(void *a, void *b) 
{
    int valA = *(int *)a;
    int valB = *(int *)b;
    return valA - valB;
}
	