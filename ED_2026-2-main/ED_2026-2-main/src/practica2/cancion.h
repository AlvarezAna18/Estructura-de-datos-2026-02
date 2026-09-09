#ifndef CANCION_H
#define CANCION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ListaD.h>
#define MAXCADENA 20

typedef struct
	{
		char nombre[MAXCADENA];
		char autor[MAXCADENA];
		short int release_date;
	}Cancion;
	
typedef struct
	{
		Cancion *cancion;
		size_t cant;
	}Canciones;

Canciones cargarCanciones(void);
void imprimirCanciones(Canciones);
void imprimirCancion(void*);
void imprimirNombre(void*);

void anterior(ListaD lista, Nodod **actual, int bucle);
void siguiente(ListaD lista, Nodod **actual, int bucle);
void imprimirReproductor(Nodod *actual, ListaD lista, int bucle);
#endif