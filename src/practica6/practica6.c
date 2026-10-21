#include "practica6.h"

//funcion captura expresion

void capturaExpresion(char expresion)
{			
			
			//ciclo para capturar el caracter en pila 
			//evaluar si es valido
			//validar si tiene parentesis y si si que sean validos osea que siempre tengan un para
			//si es valida crear un arbol
			//si no es valido mandar mensaje y regresa a menu
			
			//asignar valores a las variables ejemplo si pongo esta Expresión: x+y/a+b*c^d

			//despues preguntar los valores con los que se van a sustituir o si hay una forma mas facil
			
			
}

void evaluar expresion()
{
	//recolectar los valores en una pila sacando los valores del arbol ENORDEN
	
	//ir sacando dato por dato para evaluar el resultado tomando en cuenta la jeraquia de operaiones
	
	//rehacer el arbol en POSTORDEN
	
	//mostrar mensaje de que se evaluo correctamente
}

//liberar la memoria utilizada

//funcion que puede servir 
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