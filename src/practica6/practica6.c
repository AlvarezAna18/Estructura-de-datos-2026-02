#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "practica6.h"

// arreglo infix: la expresion original 
// arreglo postfix: la expresion acomodada
static char expInfix[100];
static char expPostfix[100];

// valor de cada variable
static float valores[128];


//jerarquia del operador
int precedencia(char op)
{
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; // parentesis y otros caracteres
}

//validar que sea un caracter valido
int esNumeroOLetra(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

int esLetra(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int esOperador(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

void imprimirChar(void *dato)
{
    if (dato != NULL)
        printf("%c", *(char*)dato);
}


//copia la expresion quitando espacios ynulo 
static void limpiarExpresion(char *entrada)
{
    int i, j = 0;
    for (i = 0; entrada[i] != '\0' && j < 99; i++)
        if (entrada[i] != ' ' && entrada[i] != '\n' && entrada[i] != '\t')
            expInfix[j++] = entrada[i];
    expInfix[j] = '\0';
}

/*
validar expresion
 parentesis  cada '(' se mete a la pila,
  cada ')' saca uno. Si al sacar la pila esta vacia, o al final
  quedan '(' en la pila, los parentesis estan mal.
*/
int validarExpresion(char *exp)
{
    Pila pila = inicializarPila(-1);
    int esperoOperando = 1;
    char *error = NULL;
    int i;

    if (exp[0] == '\0')
        error = "la expresion esta vacia";

    for (i = 0; exp[i] != '\0' && !error; i++)
    {
        char c = exp[i];

        if (esNumeroOLetra(c))
        {
            if (!esperoOperando)
                error = "hay dos operandos seguidos sin operador";
            esperoOperando = 0;
        }
        else if (c == '(')
        {
            if (!esperoOperando)
                error = "falta un operador antes de '('";
            push(&pila, &exp[i]);
        }
        else if (c == ')')
        {
            if (esperoOperando)
                error = "un operador no tiene operando derecho (o hay parentesis vacios)";
            else if (pilaVacia(pila))
                error = "hay un ')' sin su '('";
            else
                pop(&pila);
        }
        else if (esOperador(c))
        {
            if (esperoOperando)
                error = "un operador no tiene operando izquierdo";
            esperoOperando = 1;
        }
        else
            error = "hay un caracter no valido";
    }

    if (!error && esperoOperando)
        error = "el ultimo operador no tiene operando derecho";
    if (!error && !pilaVacia(pila))
        error = "hay un '(' que no se cerro";

    while (!pilaVacia(pila))   // vaciar la pila
        pop(&pila);

    if (error)
    {
        printf("\nExpresion invalida: %s.", error);
        return 0;
    }
    return 1;
}


/*
 INFIX A POSTFIX 
operando: se inserta en el arreglo postfix.
 ( : push a la pila.
 ) : pop de operadores al postfix hasta encontrar ( 
operador: pop de los operadores con precedencia mayor o igual hasta encontrar uno menor, un '(' o vaciar la pila; 
luego push del operador.
infix se vacia la pila en el postfix.
*/
void infixAPostfix(char *infix, char *postfix)
{
    Pila pila = inicializarPila(-1);
    int i, j = 0;

    for (i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        if (esNumeroOLetra(c))//validar parentesis
            postfix[j++] = c;
        else if (c == '(')
            push(&pila, &infix[i]);
        else if (c == ')')
        {
            while (*(char*)peek(pila) != '(')
                postfix[j++] = *(char*)pop(&pila);
            pop(&pila); // saca el '('
        }
        else //operador
        {
            while (!pilaVacia(pila) && c != '^' &&
                   precedencia(*(char*)peek(pila)) >= precedencia(c))
                postfix[j++] = *(char*)pop(&pila);
            push(&pila, &infix[i]);
        }
    }

    while (!pilaVacia(pila))
        postfix[j++] = *(char*)pop(&pila);
    postfix[j] = '\0';
}


/*
postfix a arbol
 Se recorre el postfix y por cada caracter se crea un nodo:
operando: push del nodo.

operador: pop -> hijo derecho, pop -> hijo izquierdo, y push del nodo.
*/

Nodoa *postfixAArbol(char *postfix)
{
    Pila pila = inicializarPila(-1);
    int i;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        char *dato = malloc(sizeof(char));
        *dato = postfix[i];
        Nodoa *nodo = crearNodoa(dato);

        if (esOperador(postfix[i]))
        {
            nodo->dch = pop(&pila);  
            nodo->izq = pop(&pila);
        }
        push(&pila, nodo);
    }
    return pop(&pila);
}


Nodoa *crearArbolDesdeInfix(char *expresion)
{
    limpiarExpresion(expresion);
    if (!validarExpresion(expInfix))
        return NULL;

    infixAPostfix(expInfix, expPostfix);
    return postfixAArbol(expPostfix);
}


//dar valor a las variables
void capturarValores(void)
{
    int capturada[128] = {0};
    int i;

    printf("\n");
    for (i = 0; expInfix[i] != '\0'; i++)
    {
        char c = expInfix[i];
        if (esLetra(c) && !capturada[(int)c]) // se pide solo la primera vez que aparece
        {
            printf("%c = ", c);
            while (scanf("%f", &valores[(int)c]) != 1)
            {
                while (getchar() != '\n'); 
                printf("valor invalido, %c = ", c);
            }
            capturada[(int)c] = 1;
        }
    }
}

//crear un arreflo devar recorria arreglo de var y postfix para insertar en el arbol buscar y capturada

float evaluarArbol(Nodoa *raiz)
{
    Pila nodos = inicializarPila(-1); //recorre el arbol
    Pila numeros = inicializarPila(-1); //guardar resultadod
    Nodoa *actual = raiz;
    Nodoa *ultimo_visitado = NULL;

    while (actual != NULL || !pilaVacia(nodos))
    {
        if (actual != NULL)
        {
            push(&nodos, actual);
            actual = actual->izq;
        }
        else
        {
            Nodoa *padre = peek(nodos);
            if (padre->dch != NULL && ultimo_visitado != padre->dch)
                actual = padre->dch;
            else
            {
   
                char c = *(char*)padre->dato;
                float *res = malloc(sizeof(float));

                if (esOperador(c))
                {
                    float *der = pop(&numeros);
                    float *izq = pop(&numeros);
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
                }
                else if (c >= '0' && c <= '9')
                    *res = c - '0';          
                else
                    *res = valores[(int)c];

                push(&numeros, res);
                ultimo_visitado = pop(&nodos);
            }
        }
    }

    float *final = pop(&numeros);
    float resultado = *final;
    free(final);
    return resultado;
}