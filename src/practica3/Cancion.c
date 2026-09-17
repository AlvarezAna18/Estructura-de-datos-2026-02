#include "Cancion.h"

void imprimir(void *dato)
{
    printf("%c", *(char*)dato);
}

void capturaCadena(Pila *pila, Cola *cola)
{
    char cadena[50];
    inputCadena("\n Captura cadena: ", cadena, 50);
    
    for(int i = 0; cadena[i] != '\0'; i++)
    {
        // Ignorar espacios y saltos de línea para el palíndromo
        if(cadena[i] != ' ' && cadena[i] != '\n' && cadena[i] != '\r')
        {
            // Reservamos memoria dinámica para que el caracter no muera al salir de la función
            char *nuevoChar = (char*)malloc(sizeof(char));
            *nuevoChar = cadena[i];
            
            push(pila, nuevoChar);
            enqueue(cola, nuevoChar);
        }
    }
}

void palindromo(Pila *pila, Cola *cola)
{
    Pila aux = inicializarPila(pila->limite);
    char temp[50];
    int n = 0;
    int esPalindromo = 1;

	//pila original a aux
    while(!pilaVacia(*pila))
    {
        Nodo *nodo = popN(pila);

        if(nodo != NULL)
        {
            temp[n] = *(char*)nodo->dato;
            n++;

           //guardar el nodo en una pila auxiliar para poder regresar la pila a su estado original
            pushN(&aux, nodo);
        }
    }

    //regresamos los nodos a la pila original.
    while(!pilaVacia(aux))
    {
        pushN(pila, popN(&aux));
    }

    // ignorando mayusculas y minusculas.
    for(int i = 0; i < n / 2; i++)
    {
        if(tolower((unsigned char)temp[i]) != tolower((unsigned char)temp[n - 1 - i]))
        {
            esPalindromo = 0;
            break;
        }
    }

    if(esPalindromo && n > 0)
    {
        printf("\n es un palindromo.\n");
    }
    else
    {
        printf("\n no es un palindromo.\n");
    }
}

void parentesis(Pila *pila)
{
    Pila aux = inicializarPila(pila->limite);
    Pila simbolos = inicializarPila(-1);

    int valido = 1;

    //pasar nodos a aux
    while(!pilaVacia(*pila))
    {
        Nodo *nodo = popN(pila);

        if(nodo != NULL)
        {
            pushN(&aux, nodo);
        }
    }

    // regresar nodos a pila original
    while(!pilaVacia(aux))
    {
        Nodo *nodo = popN(&aux);

        if(nodo != NULL)
        {
            char c = *(char*)nodo->dato;

            //si es simbolo de apertura guardamos en la pila de simbolos
            if(c == '(' || c == '{' || c == '[')
            {
                char *nuevoChar = malloc(sizeof(char));

                if(nuevoChar != NULL)
                {
                    *nuevoChar = c;
                    push(&simbolos, nuevoChar);
                }
            }

            //si es un simbolo de cierre comprobamos que corresponda con el ultimo simbolo abierto
            else if(c == ')' || c == '}' || c == ']')
            {
                if(pilaVacia(simbolos))
                {
                    valido = 0;
                }
                else
                {
                    char *abierto = (char*)pop(&simbolos);

                    if((c == ')' && *abierto != '(') ||
                       (c == '}' && *abierto != '{') ||
                       (c == ']' && *abierto != '['))
                    {
                        valido = 0;
                    }

                    free(abierto);
                }
            }
           //nodo originak a pila
            pushN(pila, nodo);
        }
    }

    //si quedao abierto
    if(!pilaVacia(simbolos))
    {
        valido = 0;
    }
    eliminarPila(&simbolos, free);

    if(valido)
    {
        printf("\n es valido\n");
    }
    else
    {
        printf("\n no es valido\n");
    }
}