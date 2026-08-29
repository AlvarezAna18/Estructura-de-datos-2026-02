#ifndef ALUMNO_H
#include <stdio.h>
#include <stdlib.h>
#include <iostring.h>
#include <string.h>

#define ALUMNO_H
#define MAX 64


typedef struct
{
	size_t matricula;
	char nombre[MAX];
	int semestre;
	float promedio;
}Alumno;

Alumno *crearAlumno(size_t);
void imprimirAlumno(void*);
int compararMatricula(void*,void*);
int compararNombre(void*,void*);
int compararSemestre(void*,void*);
int compararPromedio(void *a, void *b);
void liberarAlumno(void *a);

#endif