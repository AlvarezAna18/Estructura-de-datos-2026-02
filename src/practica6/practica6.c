#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include "practica6.h"

char variables[50];
float valores[50];
int cantidad = 0;

//saber el operando jerarquia
int precedencia(char op) 
{
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; // parentesis y caracteres
}

//validar que sea un caracter valido
int esNumeroOLetra(char c) 
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

//infix a postfix y construir arbol
Nodoa* crearArbolDesdeInfix(char *infix) 
{
    char postfix[100];
    int pos = 0;
    cantidad = 0;

    Pila pilaOps = inicializarPila(-1);

    // jerarquia
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        if (c == ' ' || c == '\n' || c == '\t') continue;

        //operando directo al arreglo postfix
        if (esNumeroOLetra(c)) {
            postfix[pos++] = c;

            // Registrar variable si es letra y no existe
            if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                int existe = 0;
                for (int j = 0; j < cantidad; j++) {
                    if (variables[j] == c) { existe = 1; break; }
                }
                if (!existe) {
                    variables[cantidad] = c;
                    valores[cantidad] = 0;
                    cantidad++;
                }
            }
        }
        //si es parentesis entra a pila
        else if (c == '(') {
            push(&pilaOps, (void*)(intptr_t)c);
        }
        //si es ) desapilar hasta (
        else if (c == ')') {
            while (!pilaVacia(pilaOps)) {
                char op = (char)(intptr_t)pop(&pilaOps);
                if (op == '(') break;
                postfix[pos++] = op;
            }
        }
        //si es un operador
        else if (precedencia(c) > 0) 
        {
            while (!pilaVacia(pilaOps)) 
            {
                char top = (char)(intptr_t)peek(pilaOps);
                //sacar de la pila si la cima es mayor o igual en precedencia
                if (top != '(' && precedencia(top) >= precedencia(c)) {
                    postfix[pos++] = (char)(intptr_t)pop(&pilaOps);
                } else {
                    break;
                }
            }
            push(&pilaOps, (void*)(intptr_t)c);
        }
    }

    //vaciar la pila 
    while (!pilaVacia(pilaOps)) {
        char op = (char)(intptr_t)pop(&pilaOps);
        if (op != '(') postfix[pos++] = op;
    }
    postfix[pos] = '\0';


    //construit arbol postfix
    Pila pilaNodos = inicializarPila(-1);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        char *dato = malloc(sizeof(char));
        *dato = c;
        Nodoa *nuevo = crearNodoa(dato);

        if (esNumeroOLetra(c)) {
            push(&pilaNodos, nuevo);
        } else {
            nuevo->dch = (Nodoa*)pop(&pilaNodos);
            nuevo->izq = (Nodoa*)pop(&pilaNodos);
            push(&pilaNodos, nuevo);
        }
    }
    
    if (pilaVacia(pilaNodos)) return NULL;
    return (Nodoa*)pop(&pilaNodos);
}

//capturar valores en variables caracteres
void capturarValores(void) 
{
    for (int i = 0; i < cantidad; i++) {
        printf("Ingrese el valor para %c: ", variables[i]);
        scanf("%f", &valores[i]);
    }
}

float obtenerValor(char c) 
{
    if (c >= '0' && c <= '9') return c - '0';
    for (int i = 0; i < cantidad; i++) {
        if (variables[i] == c) return valores[i];
    }
    return 0;
}

//evaluar arvol postordemm
float evaluarArbol(Nodoa *raiz) 
{
    if (!raiz) return 0;

    Pila pila = inicializarPila(-1);
    Pila pilaPostorden = inicializarPila(-1);
    Pila pilaValores = inicializarPila(-1);

    push(&pila, raiz);

    //recorrido Postorden
    while (!pilaVacia(pila)) {
        Nodoa *actual = (Nodoa*)pop(&pila);
        push(&pilaPostorden, actual);

        if (actual->izq) push(&pila, actual->izq);
        if (actual->dch) push(&pila, actual->dch);
    }

    //evaluar  el operando 
    while (!pilaVacia(pilaPostorden)) 
    {
        Nodoa *nodo = (Nodoa*)pop(&pilaPostorden);
        char c = *(char*)nodo->dato;

        if (esNumeroOLetra(c)) 
        {
            float *val = malloc(sizeof(float));
            *val = obtenerValor(c);
            push(&pilaValores, val);
        } 
        else 
        {
            float *der = (float*)pop(&pilaValores);
            float *izq = (float*)pop(&pilaValores);
            float *res = malloc(sizeof(float));

            switch (c) 
            {
                case '+': *res = *izq + *der; break;
                case '-': *res = *izq - *der; break;
                case '*': *res = *izq * *der; break;
                case '/': *res = (*der == 0) ? 0 : (*izq / *der); break;
                case '^': *res = powf(*izq, *der); break;
            }

            free(izq);
            free(der);
            push(&pilaValores, res);
        }
    }

    float *resPtr = (float*)pop(&pilaValores);
    float resultado = *resPtr;
    free(resPtr);

    return resultado;
}

void imprimirChar(void *dato) 
{
    if (dato != NULL) {
        printf("%c", *(char*)dato);
    }
}