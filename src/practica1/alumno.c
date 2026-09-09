#include "alumno.h"


Alumno *crearAlumno(size_t matricula)
{
	Alumno *nuevo = calloc(1,sizeof(Alumno));
	nuevo->matricula = matricula;
	inputCadena("Captura nombre: ",nuevo->nombre,MAX);
	inputEntero("Captura semestre: ",&nuevo->semestre);
	inputFloat("Captura promedio: ",&nuevo->promedio);
	return nuevo;
}


void imprimirAlumno(void *a)
{	
	Alumno alumno = *(Alumno*)a;
	printf("%-8llu | ",alumno.matricula);
	printf("%-20s | ",alumno.nombre);
	printf("%3d | ",alumno.semestre);
	printf("%.2f | ",alumno.promedio);
}

int compararMatricula(void *a, void *b)
{
	//asignar valores a y b
	Alumno *alumnoA = (Alumno *)a;
    Alumno *alumnoB = (Alumno *)b;

    if(alumnoA->matricula > alumnoB->matricula)//si matricula a es mayor que b
        return 1;

    if(alumnoA->matricula < alumnoB->matricula)//si matricula a es menor que b
        return -1;

    return 0;
}
int compararNombre(void *a, void *b)
{
	//asignar valores a y b
	Alumno *alumnoA = (Alumno *)a;
    Alumno *alumnoB = (Alumno *)b;

    return strcmp(alumnoA->nombre,alumnoB->nombre);//utilizar strcmp para comparar
}
int compararSemestre(void *a, void *b)
{
	//asignar valores a y b
	Alumno *alumnoA = (Alumno *)a;
    Alumno *alumnoB = (Alumno *)b;

    if(alumnoA->semestre > alumnoB->semestre)//si el semestre a es mayor al b 
        return 1;

    if(alumnoA->semestre < alumnoB->semestre)
        return -1;

    return 0;
}
int compararPromedio(void *a, void *b)
{
	//asignar valores a y b
    Alumno *alumnoA = (Alumno *)a;
    Alumno *alumnoB = (Alumno *)b;


	//comparo los promedios y devuelvo diferente valor dependiendo si es mayor 1 o menor -1
    if(alumnoA->promedio > alumnoB->promedio)
        return 1;

    if(alumnoA->promedio < alumnoB->promedio)
        return -1;

    return 0;
}

void liberarAlumno(void *a)
{
    free(a);
}