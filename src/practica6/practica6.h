#ifndef PRACTICA6_H
#define PRACTICA6_H
 
#include "arbol.h"
 
int precedencia(char op);
int esNumeroOLetra(char c);
int esLetra(char c);
int esOperador(char c);
void imprimirChar(void *dato);
 
int validarExpresion(char *exp);
void infixAPostfix(char *infix, char *postfix);
Nodoa *postfixAArbol(char *postfix);
Nodoa *crearArbolDesdeInfix(char *expresion);
 
void capturarValores(void);
void imprimirConValores(void);
float evaluarArbol(Nodoa *raiz);
 
#endif
 