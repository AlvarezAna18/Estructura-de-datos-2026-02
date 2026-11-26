#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <iostring.h>
#include <HashQ.h>
#include <arbol.h>
#include "Libro.h"

int folding(void *);

int main(void)
{
	setbuf(stdout, NULL);

	// Tabla base igual a la del profe (con primo 101 para que no se cicle)
	HashQTable tablahash;
	tablahash.table = calloc(101,sizeof(void*));
	tablahash.len = 101;
	tablahash.cant = 0;
	tablahash.min = 30;
	tablahash.max = 70;
	tablahash.fixed = (tablahash.min+tablahash.max)/2;
	tablahash.folding = folding;
	tablahash.imprimir = imprimirLibro;
	tablahash.comparar = compararTitulo;
	tablahash.verbose = 0;

	HashQTable tablaISBN = tablahash;
	tablaISBN.table = calloc(101,sizeof(void*));
	tablaISBN.folding = foldingISBN;
	tablaISBN.comparar = compararISBN;

	HashQTable tablaAutor = tablahash;
	tablaAutor.table = calloc(101,sizeof(void*));
	tablaAutor.folding = foldingAutor;
	tablaAutor.comparar = compararAutor;

	HashQTable tablaFecha = tablahash;
	tablaFecha.table = calloc(101,sizeof(void*));
	tablaFecha.folding = foldingFecha;
	tablaFecha.comparar = compararFecha;

	HashQTable tablaIniTitulo = tablahash;
	tablaIniTitulo.table = calloc(101,sizeof(void*));
	tablaIniTitulo.folding = foldingIniTitulo;
	tablaIniTitulo.comparar = compararIniTitulo;

	HashQTable tablaIniAutor = tablahash;
	tablaIniAutor.table = calloc(101,sizeof(void*));
	tablaIniAutor.folding = foldingIniAutor;
	tablaIniAutor.comparar = compararIniAutor;

	Acervo acervo = obtener_libros();
	for(int i = 0; i < acervo.cantidad ; i++)
	{
		fn_insertKey(&tablahash,acervo.libros+i);
		fn_insertKey(&tablaISBN,acervo.libros+i);
		fn_insertKey(&tablaAutor,acervo.libros+i);
		fn_insertKey(&tablaFecha,acervo.libros+i);
		fn_insertKey(&tablaIniTitulo,acervo.libros+i);
		fn_insertKey(&tablaIniAutor,acervo.libros+i);
	}
	remap(&tablahash);
	remap(&tablaISBN);
	remap(&tablaAutor);
	remap(&tablaFecha);
	remap(&tablaIniTitulo);
	remap(&tablaIniAutor);

	int opcion = 0, sub = 0, a1, a2;
	char ini, fin;
	Libro buscado;

	do
	{
		printf("\n. . . ACERVO BIBLIOGRAFICO . . .");
		printf("\n1. Buscar por ISBN");
		printf("\n2. Buscar por titulo");
		printf("\n3. Buscar por autor");
		printf("\n4. Buscar por fecha");
		printf("\n5. Administrar acervo");
		printf("\n6. Salir");
		if (inputEntero("\nOpcion: ", &opcion) != 1) opcion = -1;

		switch (opcion)
		{
			case 1:
			{
				inputCadena("ISBN: ", buscado.isbn, MAX_ISBN);
				Libro *aqui = fn_searchKey(&tablaISBN, &buscado);
				if (aqui)
				{
					printf("\nLIBRO ENCONTRADO:\n");
					imprimirLibro(aqui);
					printf("\n");
				}
				else printf("\nNo se encontro ese ISBN\n");
				break;
			}

			case 2:
			{
				printf("\n1. Titulo exacto\n2. Rango de iniciales");
				if (inputEntero("\nOpcion: ", &sub) != 1) sub = -1;
				if (sub == 1)
				{
					inputCadena("Titulo: ", buscado.titulo, MAX_TITULO);
					Libro *aqui = fn_searchKey(&tablahash, &buscado);
					if (aqui)
					{
						printf("\nLIBRO ENCONTRADO:\n");
						imprimirLibro(aqui);
						printf("\n");
					}
					else printf("\nNo se encontro ese titulo\n");
				}
				else if (sub == 2)
				{
					inputChar("Inicial inferior: ", &ini);
					inputChar("Inicial superior: ", &fin);
					ini = toupper((unsigned char)ini);
					fin = toupper((unsigned char)fin);
					if (ini > fin) { char aux = ini; ini = fin; fin = aux; }

					Arbol arbol = {NULL, 0, cmpArbolTitulo, ASC};
					for (char c = ini; c <= fin; c++)
					{
						buscado.titulo[0] = c;
						buscado.titulo[1] = '\0';
						recolectar(&tablaIniTitulo, &buscado, &arbol);
					}
					mostrarResultados(&arbol);
				}
				else printf("\nOpcion invalida\n");
				break;
			}

			case 3:
			{
				printf("\n1. Nombre de autor\n2. Rango de iniciales");
				if (inputEntero("\nOpcion: ", &sub) != 1) sub = -1;
				if (sub == 1)
				{
					inputCadena("Autor: ", buscado.autor, MAX_AUTOR);
					Arbol arbol = {NULL, 0, cmpArbolFecha, ASC};
					recolectar(&tablaAutor, &buscado, &arbol);
					mostrarResultados(&arbol);
				}
				else if (sub == 2)
				{
					inputChar("Inicial inferior: ", &ini);
					inputChar("Inicial superior: ", &fin);
					ini = toupper((unsigned char)ini);
					fin = toupper((unsigned char)fin);
					if (ini > fin) { char aux = ini; ini = fin; fin = aux; }

					Arbol arbol = {NULL, 0, cmpArbolAutor, ASC};
					for (char c = ini; c <= fin; c++)
					{
						buscado.autor[0] = c;
						buscado.autor[1] = '\0';
						recolectar(&tablaIniAutor, &buscado, &arbol);
					}
					mostrarResultados(&arbol);
				}
				else printf("\nOpcion invalida\n");
				break;
			}

			case 4:
			{
				printf("\n1. Anio exacto\n2. Rango de anios");
				if (inputEntero("\nOpcion: ", &sub) != 1) sub = -1;
				if (sub == 1 && inputEntero("Anio: ", &buscado.fecha) == 1)
				{
					Arbol arbol = {NULL, 0, cmpArbolTitulo, ASC};
					recolectar(&tablaFecha, &buscado, &arbol);
					mostrarResultados(&arbol);
				}
				else if (sub == 2 && inputEntero("Anio inferior: ", &a1) == 1 && inputEntero("Anio superior: ", &a2) == 1)
				{
					if (a1 > a2) { int aux = a1; a1 = a2; a2 = aux; }
					Arbol arbol = {NULL, 0, cmpArbolFecha, ASC};
					for (int a = a1; a <= a2; a++)
					{
						buscado.fecha = a;
						recolectar(&tablaFecha, &buscado, &arbol);
					}
					mostrarResultados(&arbol);
				}
				else printf("\nOpcion o anio invalido\n");
				break;
			}


			case 5:
			{
					printf("\n1. Eliminar por ISBN\n2. Ver tabla hash");
					if (inputEntero("\nOpcion: ", &sub) != 1) sub = -1;
					if (sub == 1)
						{
							inputCadena("ISBN a eliminar: ", buscado.isbn, MAX_ISBN);
							Libro *objetivo = fn_searchKey(&tablaISBN, &buscado);
							if (objetivo)
								{
									borrarDeTabla(&tablaISBN, objetivo);
									borrarDeTabla(&tablahash, objetivo);
									borrarDeTabla(&tablaAutor, objetivo);
									borrarDeTabla(&tablaFecha, objetivo);
									borrarDeTabla(&tablaIniTitulo, objetivo);
									borrarDeTabla(&tablaIniAutor, objetivo);

									printf("\nLIBRO ELIMINADO DE TODAS LAS TABLAS:\n");
									imprimirLibro(objetivo);
									printf("\n");
								}
							else printf("\nNo existe ese ISBN\n");
							}
							else if (sub == 2)
							{
								printf("\nTABLA ISBN");
								for(int i = 0; i < tablaISBN.len ; i++)
								{
									printf("\n[%d] ",i);
									if(tablaISBN.table[i]!=NULL && tablaISBN.table[i]!=&tablaISBN)
										imprimirLibro(tablaISBN.table[i]);
								}
								printf("\n");
							}
							else printf("\nOpcion invalida\n");
							break;
				}
				case 6:
					break;

				default:
					printf("\nOpcion invalida\n");
			}
		} while (opcion != 6);

		printf("\n\n FIN DE PROGRAMA\n");
		return 0;
}

int folding(void *data)
{
	char *cadena = ((Libro*)data)->titulo;
	int key = 0,sector = 1,sumatoria=0;
	for(int i = 0; cadena[i]!='\0'; i++)
	{
		//abc de
		sumatoria += cadena[i];
		if( i!=0 && (i+1)%3 == 0)
		{
			key+= sector*sumatoria;
			sumatoria = 0;
			sector++;
		}
	}	
	key+= sector*sumatoria;
	return key;
}