#include "Cancion.h"
Canciones cargarCanciones(void)
{
	static Cancion biblioteca[] =
	{
		(Cancion){"Despacito","Luis Fonsi",2017},
		(Cancion){"Karmadame","Zoe",2020},
		(Cancion){"Luna","zoe",2008},
		(Cancion){"Amantes Suicidas","Mon Laferte",2024},
		(Cancion){"Everywhere","Fleetwood mac",1987},
		(Cancion){"Moving","Kate Bush",1978},
		(Cancion){"Mary On A Cross","Ghost",2019},
		(Cancion){"Dance Macabre","Ghost",2018},
		(Cancion){"Training Wheels","Melanie Martinez",2015},
		(Cancion){"The Boy Is Mine","Monica Brandy",1998},
		(Cancion){"Tu Falta de Querer","Mon Laferte",2014},
		(Cancion){"Amarte duele","Natalia Lafourcade",2002},
		(Cancion){"Azul","Zoe",2018},
		(Cancion){"Entre canibsles","Soda Stereo",1990},

	};

	static Canciones canciones;
	canciones.cancion = biblioteca;
	canciones.cant = sizeof(biblioteca)/sizeof(Cancion);
	return canciones;
}

void imprimirCanciones(Canciones canciones)
	{
		printf("\n Canciones TOTAL:%zu",canciones.cant);
		for(int i = 0 ; i< canciones.cant; i++)
		{
		printf("\n[%d]",i);
		imprimirCancion(&canciones.cancion[i]);
		}
	}
	
void imprimirCancion(void *dato)
	{
	Cancion *cancion = dato;
	printf(" %-20s ",cancion->nombre);
	printf("| %-20s ",cancion->autor);
	printf("| %hu ",cancion->release_date);
	}
	
void imprimirNombre(void *dato)
	{
		Cancion *cancion = dato;
		printf(" %-20s ",cancion->nombre);
	}
	
//se mueve la cola de reproduccion (lista) 
void anterior(ListaD lista, Nodod **actual, int bucle)
	{
		if(*actual)
		{
			if((*actual)->ant)
				*actual = (*actual)->ant;//si hay una cancion antes
			else if(bucle)
				*actual = lista.fin;//si esta encendido el bucle se va a fin 
		}
	}

void siguiente(ListaD lista, Nodod **actual, int bucle)
	{
		if(*actual)
		{
			if((*actual)->sig)
				*actual = (*actual)->sig;//si hay cancion despues asigna sig
			else if(bucle)
				*actual = lista.inicio;//asigna inicio a actual si hay bucle
		}
	}

void imprimirReproductor(Nodod *actual, ListaD lista, int bucle)
	{
		
		if(!actual)//si es dif a actual
		{
			printf("\n No hay canciones en la cola de reproduccion");
			return;
		}

		// ANTERIOR -> ACTUAL -> SIGUIENTE
		printf("\n ");

		if(actual->ant)//actual a anterior
			imprimirNombre(actual->ant->dato);
		else if(bucle)
			imprimirNombre(lista.fin->dato);//si es bucle manda fin
		else
			printf(" %-20s ", " ");

		printf(" -> [");
		imprimirNombre(actual->dato);
		printf("] -> ");

		if(actual->sig)//si actual a sig
			imprimirNombre(actual->sig->dato);
		else if(bucle)
			imprimirNombre(lista.inicio->dato);//si hay bucle imprime inicio
		else
			printf(" %-20s ", " ");

		printf("\n");
	}
 