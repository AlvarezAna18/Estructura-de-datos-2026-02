#ifndef LIBRO_H
#define LIBRO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <iostring.h>
#include <HashQ.h>
#include <arbol.h>

#define CANT_LIBROS 50
#define MAX_ISBN 20
#define MAX_TITULO 45
#define MAX_AUTOR 30

#define TAM_INICIAL 101

typedef struct
{
    char isbn[MAX_ISBN];
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int fecha;
    int disponible;
} Libro;

typedef struct
{
    size_t cantidad;
    Libro *libros;
} Acervo;

typedef struct
{
    HashQTable isbn;
    HashQTable titulo;
    HashQTable autor;
    HashQTable fecha;
    HashQTable iniTitulo;
    HashQTable iniAutor;
} Biblioteca;

//Funciones base
Acervo obtener_libros(void);
void imprimirLibro(void *vlibro);
void imprimirConSalto(void *vlibro);

// Folding y comparacion para HashQ
int foldingISBN(void *data);
int foldingTitulo(void *data);
int foldingAutor(void *data);
int foldingFecha(void *data);
int foldingIniTitulo(void *data);
int foldingIniAutor(void *data);

int compararISBN(void *a, void *b);
int compararTitulo(void *a, void *b);
int compararAutor(void *a, void *b);
int compararFecha(void *a, void *b);
int compararIniTitulo(void *a, void *b);
int compararIniAutor(void *a, void *b);

//Comparadores para el Arbol
int cmpArbolTitulo(void *a, void *b);
int cmpArbolFecha(void *a, void *b);
int cmpArbolAutor(void *a, void *b);

//Funciones de Biblioteca
void iniciarBiblioteca(Biblioteca *b);
void cargarAcervo(Biblioteca *b, Acervo acervo);
void liberarBiblioteca(Biblioteca *b);

int buscarISBN(Biblioteca *b, char *isbn);
int buscarTitulo(Biblioteca *b, char *titulo);
int buscarRangoTitulo(Biblioteca *b, char ini, char fin);
int buscarAutor(Biblioteca *b, char *autor);
int buscarRangoAutor(Biblioteca *b, char ini, char fin);
int buscarFecha(Biblioteca *b, int anio);
int buscarRangoFecha(Biblioteca *b, int ini, int fin);

Libro* eliminarLibro(Biblioteca *b, char *isbn);
void verTablaHash(Biblioteca *b);
void recolectar(HashQTable *t, Libro *buscado, Arbol *arbol);
void mostrarResultados(Arbol *arbol);
void borrarDeTabla(HashQTable *t, Libro *objetivo);
#endif