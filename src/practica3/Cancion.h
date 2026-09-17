#ifndef CANCION_H
#define CANCION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostring.h>
#include <Pila.h>
#include <Cola.h>
#include <ctype.h>

void imprimir(void *dato);
void capturaCadena(Pila *pila, Cola *cola);
void palindromo(Pila *pila, Cola *cola);
void parentesis(Pila *pila); 

#endif