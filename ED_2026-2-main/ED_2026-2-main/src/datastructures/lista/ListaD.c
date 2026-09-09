#include "ListaD.h"
ListaD inicializarListaD(void)
	{
		return (ListaD){.inicio=NULL,.fin=NULL,.cant=0,.orden=NINGUNO,.comparar=NULL,.circular=0};//agrege circular
	}
void insertarOrdenadoD(ListaD *lista,void *dato)
{
	if(!lista->inicio || lista->comparar(dato,lista->inicio->dato) < 0)
	insertarInicioD(lista,dato);
	else if( lista->comparar(dato,lista->fin->dato) > 0)
	insertarFinalD(lista,dato);
	else
	{
		Nodod *nuevo = crearNodod(dato);
		Nodod *q = lista->inicio;
		Nodod *p = q->sig;
	while( lista->comparar(dato,p->dato) > 0)
	{
		q = p;
		p = p->sig;
	}
	
	q->sig = nuevo;
	nuevo->ant = q;
	nuevo->sig = p;
	p->ant = nuevo;
	lista->cant++;}
}

void imprimirListaIFD(ListaD lista,fn_imprimir imprimir)
{
	if(!lista.inicio) return;
	Nodod *aux = lista.inicio;
	do
	{
	printf("\n");
	imprimir(aux->dato);
	aux = aux->sig;
	}while( aux && aux!= lista.inicio);
}

void imprimirListaFID(ListaD lista,fn_imprimir imprimir)
{
	if(!lista.inicio) return;
	Nodod *aux = lista.fin;
	do
	{
		printf("\n");
		imprimir(aux->dato);
		aux = aux->ant;
	}while( aux && aux!= lista.fin);
}

//-----------------------------------------------------------------------------------------------------------
void eliminarListaD(ListaD *lista,fn_free liberar)
{
	// Si la lista no existe o está vacía, no hacemos nada
	if (lista == NULL || lista->inicio == NULL)
	return;
	Nodod *actual = lista->inicio;
	Nodod *siguiente;
	//si la lista es circular, cortamos el ciclo para que el while no de vueltas infinitas
	if(lista->fin)
	lista->fin->sig = NULL;
		while (actual != NULL)
		{
			siguiente = actual->sig; // Guardamos la dirección del siguiente nodo
			// Si nos pasaron una función para liberar el dato, la usamos
			if (liberar != NULL)
			liberar(actual->dato);
			free(actual); // Liberamos el nodo actual
			actual = siguiente;
		}
	// Dejamos la lista limpia
	lista->inicio = NULL;
	lista->fin = NULL;
	lista->cant = 0;
	lista->circular = 0;
}

void insertarInicioD(ListaD *lista,void *dato)
{
	Nodod *nuevo = crearNodod(dato);
	if(!lista->inicio)
	lista->inicio = lista->fin = nuevo;
	else
	{
	nuevo->sig = lista->inicio;
	lista->inicio->ant = nuevo;
	lista->inicio = nuevo;
	}
	lista->cant++;
	//si la cola de reproduccion esta en modo bucle, se vuelve a cerrar el circulo
	if(lista->circular)
	{
		lista->fin->sig = lista->inicio;
		lista->inicio->ant = lista->fin;
	}
}

void insertarFinalD(ListaD *lista,void *dato)
{
	Nodod *nuevo = crearNodod(dato);
	if(!lista->inicio)lista->inicio = lista->fin = nuevo;
	else
	{
		nuevo->ant = lista->fin;
		lista->fin->sig = nuevo;
		lista->fin = nuevo;
	}
	lista->cant++;
	if(lista->circular)
	{
		lista->fin->sig = lista->inicio;
		lista->inicio->ant = lista->fin;
	}
}
//------------------------------------------------------------------------------------------
void eliminarDatoD(ListaD *lista,void *dato,fn_comparar comparar)
{
	if (lista == NULL || lista->inicio == NULL)
	return;
	Nodod *actual = lista->inicio;
	do
	{
	// Si encontramos el dato a eliminar
	if (comparar(dato, actual->dato) == 0)
	{
	eliminarNodoD(lista,actual,NULL);
	return;
	}
	actual = actual->sig; // seguir buscacndo
	}while(actual != NULL && actual != lista->inicio);
}

int buscarDatoD(ListaD lista,void *dato,fn_comparar comparar)
{
	Nodod *actual = lista.inicio;
	if(!actual) return 0;
	do
	{
	// Si comparar da 0, significa que los datos son iguales
	if (comparar(dato, actual->dato) == 0)
	{
		return 1; // Lo encontró
	}
		actual = actual->sig; // Avanza al siguiente nodo
	}while(actual != NULL && actual != lista.inicio);
	return 0;//si no encuentra
}

void ordenarListaD(ListaD *lista,fn_comparar comparar,Orden orden)
{
if (lista == NULL || lista->inicio == NULL || orden == NINGUNO) //validar que exista
return;
//asignar variables a comparar y orden
lista->comparar = comparar;
lista->orden = orden;
	for (Nodod *i = lista->inicio; i != NULL; i = i->sig)
	{
		for (Nodod *j = i->sig; j != NULL; j = j->sig)
		{
		int res = comparar(i->dato, j->dato);//compara datos
		// Si es ASCENDENTE y 'i' es mayor que 'j', o
		// si es DESCENDENTE y 'i' es menor que 'j', los intercambiamos
			if ((orden == ASCENDENTE && res > 0) || (orden == DESCENDENTE && res < 0))
			{
			void *temp = i->dato;
			i->dato = j->dato;
			j->dato = temp;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------------------------
//busca el nodo que esta en la posicion 0 = inicio
Nodod* obtenerNodoD(ListaD lista,int pos)
{
	if(!lista.inicio || pos < 0 || pos >= (int)lista.cant)
	return NULL;
	Nodod *aux = lista.inicio;
	for(int i = 0; i < pos; i++)
	aux = aux->sig;
	return aux;
}
//inseratr dato en pos de la cola de reproduccion (0 = inicio, cant = final)
void insertarPosicionD(ListaD *lista,void *dato,int pos)
{
	if(lista == NULL || pos < 0 || pos > (int)lista->cant)
	return;
	if(pos == 0)
	{
		insertarInicioD(lista,dato);
		return;
	}
	if(pos == (int)lista->cant)
	{
		insertarFinalD(lista,dato);
		return;
	}
	
	Nodod *q = obtenerNodoD(*lista,pos - 1); //nodo que quedara antes del nuevo
	Nodod *p = q->sig; //nodo que quedara despues del nuevo
	Nodod *nuevo = crearNodod(dato);
	q->sig = nuevo;
	nuevo->ant = q;
	nuevo->sig = p;
	p->ant = nuevo;
	lista->cant++;
}

//eliminar nodo
void eliminarNodoD(ListaD *lista,Nodod *nodo,fn_free liberar)
{
	if(lista == NULL || nodo == NULL)
	return;
	if(lista->cant <= 1)
	{
		//era el unico nodo de la lista
		lista->inicio = NULL;
		lista->fin = NULL;
	}
	else
	{
		nodo->ant->sig = nodo->sig;
		nodo->sig->ant = nodo->ant;
		
		if(nodo == lista->inicio)
		lista->inicio = nodo->sig;
		if(nodo == lista->fin)
		lista->fin = nodo->ant;
	}
	
	if(liberar != NULL)
	liberar(nodo->dato);
	free(nodo);
	lista->cant--;
}
 