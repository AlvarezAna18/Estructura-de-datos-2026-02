#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <Lista.h>
#include "alumno.h"

int main(void)
{	
//------------------------------------------------------------------------

Lista lista = inicializarLista();

    int opcion;
    int opc;
    int orden;
	char ch;
	

    do
    {
        // MENU
        printf("\n\n Bienvenidos :) ");
        printf("\n1. Registrar Alumno");
        printf("\n2. Desplegar Alumnos");
        printf("\n3. Reordenar");
        printf("\n4. Buscar Alumno");
        printf("\n5. Borrar Alumno");
        printf("\n6. Salir");

        printf("\nOpcion: ");
        scanf("%d", &opcion);

        while((ch = getchar()) != '\n' && ch != EOF);


        switch(opcion)
        {

        //Registrar alumno
        case 1:
			{
				Alumno alumno;

				printf("\nCaptura matricula: ");
				scanf("%llu", &alumno.matricula);
				clear_buffer();

				if(buscarDato(lista, &alumno, compararMatricula))
				{	
					printf("\nMatricula ya existente");
				}
				else
				{
					Alumno *nuevo = crearAlumno(alumno.matricula);
					//insertar odenada
					registraOrdenado(&lista, nuevo);
				}

				break;
			}

       //Desplegar Alumnos
        case 2:

            imprimirLista(lista,imprimirAlumno);

            break;


        //caso reordenar
        case 3:

            printf("\nReordenar por tipo de dato:");
            printf("\n1. Matricula");
            printf("\n2. Nombre");
            printf("\n3. Semestres");
            printf("\n4. Promedio");
            printf("\nOpcion: ");
            scanf("%d", &opc);

			printf("\nComo te gustaria el orden?");
            printf("\n1. Ascendente");
            printf("\n2. Descendente");

            printf("\nOpcion: ");
            scanf("%d", &orden);

			//validacion dependiendo tipo de dato
			//tipo de orden matricula
            if(opc == 1)
            {
                if(orden == 1)
                    ordenarLista(&lista, compararMatricula, ASCENDENTE);

                else if(orden == 2)
                    ordenarLista(&lista, compararMatricula, DESCENDENTE);

                else
                    printf("\nOrden invalido.");
            }

			//tipo de orden nombre
            else if(opc == 2)
            {
                if(orden == 1)
                    ordenarLista(&lista, compararNombre, ASCENDENTE);

                else if(orden == 2)
                    ordenarLista(&lista, compararNombre, DESCENDENTE);

                else
                    printf("\nOrden invalido.");
            }

			//semestre
            else if(opc == 3)
            {
                if(orden == 1)
                    ordenarLista(&lista, compararSemestre, ASCENDENTE);

                else if(orden == 2)
                    ordenarLista(&lista, compararSemestre, DESCENDENTE);

                else
                    printf("\nOrden invalido.");
            }

			//tipo de orden promedio
            else if(opc == 4)
            {
                if(orden == 1)
                    ordenarLista(&lista, compararPromedio, ASCENDENTE);

                else if(orden == 2)
                    ordenarLista(&lista, compararPromedio, DESCENDENTE);

                else
                    printf("\nOrden invalido.");
            }

            else
            {
                printf("\nCriterio no valido :( ");
            }

            break;
			
		//buscar alumno
        case 4:
        {
            Alumno buscado;
            Nodo *aux;
			int criterio;
            printf("\nBuscar por:");
            printf("\n1. Matricula");
            printf("\n2. Nombre");
            printf("\n3. Semestres");
            printf("\n4. Promedio");

            printf("\nOpcion: ");
            scanf("%d", &criterio);
            while((ch = getchar()) != '\n' && ch != EOF);

		//se aplica de la misma manera que ordenar 
		
		//buscar matricula
            if(criterio == 1)
            {
                printf("\nMatricula: ");
                scanf("%llu", &buscado.matricula);
                aux = lista.inicio;

                while(aux != NULL)
                {
                    if(compararMatricula(&buscado, aux->dato) == 0)
                    {
                        printf("\nAlumno encontrado:");
                        imprimirAlumno(aux->dato);
                        break;
                    }

                    aux = aux->sig;
                }

                if(aux == NULL)
                    printf("\nAlumno no encontrado.");
            }


            //buscar nombre
            else if(criterio == 2)
            {
                printf("\nNombre: ");
                fgets(buscado.nombre, 64, stdin);

                buscado.nombre[strcspn(buscado.nombre, "\n")] = '\0';

                aux = lista.inicio;

                while(aux != NULL)
                {
                    if(compararNombre(&buscado, aux->dato) == 0)
                    {
                        printf("\nAlumno encontrado:");
                        imprimirAlumno(aux->dato);
                        break;
                    }

                    aux = aux->sig;
                }

                if(aux == NULL)
                    printf("\nAlumno no encontrado.");
            }


            //buscar por semestre
            else if(criterio == 3)
            {
                printf("\nSemestres: ");
                scanf("%d", &buscado.semestre);

                aux = lista.inicio;

                while(aux != NULL)
                {
                    if(compararSemestre(&buscado, aux->dato) == 0)
                    {
                        printf("\nAlumno encontrado:");
                        imprimirAlumno(aux->dato);
                        break;
                    }

                    aux = aux->sig;
                }

                if(aux == NULL)
                    printf("\nAlumno no encontrado.");
            }


			//buscra por promedio
            else if(criterio == 4)
            {
                printf("\nPromedio: ");
                scanf("%f", &buscado.promedio);

                aux = lista.inicio;

                while(aux != NULL)
                {
                    if(compararPromedio(&buscado, aux->dato) == 0)
                    {
                        printf("\nAlumno encontrado:");
                        imprimirAlumno(aux->dato);
                        break;
                    }

                    aux = aux->sig;
                }

                if(aux == NULL)
                    printf("\nAlumno no encontrado.");
            }

			//si no aplica ninguno
            else
            {
                printf("\nFiltro invalido.");
            }

            break;
        }


        //borrar alumno
        case 5:
        {
            Alumno buscado;

            printf("\nMatricula del alumno a borrar: ");
            scanf("%llu", &buscado.matricula);

            eliminarDato(&lista, &buscado, compararMatricula);
            break;
        }

        case 6:

            printf("\n\n FIN DE PROGRAMA :) ");
            break;

        default:
            printf("\nOpcion invalida.\n");
        }

    }
    while(opcion != 6);
	
	eliminarLista(&lista, liberarAlumno);
    return 0;
}

