#ifndef PRACTICA6_H
#define PRACTICA6_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arbol.h"

//prototiopos
int precedencia(char op);
int esNumeroOLetra(char c);
Nodoa* crearArbol(char *texto);
void pedirValores(void);
float obtenerValor(char c);
float evaluarArbol(Nodoa *raiz);
void imprimirCaracter(void *dato);

#endif