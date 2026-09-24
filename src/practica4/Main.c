#include <stdio.h>
#include <stdlib.h>
#include <Pila.h>
#include <iostring.h>
#include "Laberinto.h"

Pila* resolverLab(Laberinto lab, Coordenada origen,Coordenada destino);

int main(void)
{
    Laberinto lab = crear_laberinto();
	//movimientos mov
	Coordenada origen = {1,1}; 
	Coordenada destino = {25,24};
	unsigned int nuevasCoor = 0;	
	inputEnteroSinSigno("\n Nuevas coordenadas? (1:SI 0:NO) : ",&nuevasCoor);
	
	if(nuevasCoor)
	{
		inputEntero("\n Captura Origen X: ",&origen.x);
		inputEntero(" Captura Origen Y: ",&origen.y);
		inputEntero("\n Captura Destino X: ",&destino.x);
		inputEntero(" Captura Destino Y: ",&destino.y);
	}
	setOrigen(lab,origen);
	setDestino(lab,destino);	
	
	Pila *pila = resolverLab(lab,origen,destino);
	
	//validar si tiene solucion o no
	if (pilaVacia(*pila))
    {
        printf("\n\n el laberinto no tiene solucion para estas coordenadas.\n\n");
    }
	
	liberarLaberinto(lab);
	eliminarPila(pila,free);
	free(pila);
	
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
}



Pila* resolverLab(Laberinto lab, Coordenada origen, Coordenada destino)
{
    Pila *pila = crearPila();
    *pila = inicializarPila(-1);    
    Coordenada *punto;
    
    //origen
    punto = crearCoordenada(origen.x, origen.y);
    push(pila, punto);  
    
    while (!pilaVacia(*pila))
    {        
        punto = (Coordenada*)peek(*pila);
        
        //validar si ya llegamos
        if (punto->x == destino.x && punto->y == destino.y)
        {
            printf("\n encontraste el destino yayyy!\n");
			        printf("\n ");
					imprimirLab(lab);
					printf("\n ");
            break; 
        }
        
        Movimientos mov = movimientosPosibles(lab, *punto);
        int seMovio = 0; //para saber si se movio
        
        //prioridades de movimiento
        // ABAJO
        if (mov.down && !seMovio)
        {
            Coordenada *nuevo = crearCoordenada(punto->x + 1, punto->y);
            push(pila, nuevo);
            if (lab[nuevo->x][nuevo->y] != 'B' && lab[nuevo->x][nuevo->y] != 'A') 
                lab[nuevo->x][nuevo->y] = '.';
            seMovio = 1;
        }
        // IZQUIERDA
        if (mov.left && !seMovio)
        {
            Coordenada *nuevo = crearCoordenada(punto->x, punto->y - 1);
            push(pila, nuevo);
            if (lab[nuevo->x][nuevo->y] != 'B' && lab[nuevo->x][nuevo->y] != 'A') 
                lab[nuevo->x][nuevo->y] = '.';
            seMovio = 1;
        }
        // ARRIBA
        if (mov.up && !seMovio)
        {
            Coordenada *nuevo = crearCoordenada(punto->x - 1, punto->y);
            push(pila, nuevo);
            if (lab[nuevo->x][nuevo->y] != 'B' && lab[nuevo->x][nuevo->y] != 'A') 
                lab[nuevo->x][nuevo->y] = '.';
            seMovio = 1;
        }
        // DERECHA
        if (mov.right && !seMovio)
        {
            Coordenada *nuevo = crearCoordenada(punto->x, punto->y + 1);
            push(pila, nuevo);
            if (lab[nuevo->x][nuevo->y] != 'B' && lab[nuevo->x][nuevo->y] != 'A') 
                lab[nuevo->x][nuevo->y] = '.';
            seMovio = 1;
        }
        
        // si no se pudo mover a ningun lado
        if (!seMovio)
        {
            Coordenada *eliminado = (Coordenada*)pop(pila);
            
            //poner o si no hay salida y si no es a ni b
            if (lab[eliminado->x][eliminado->y] != 'A' && lab[eliminado->x][eliminado->y] != 'B')
            {
                lab[eliminado->x][eliminado->y] = 'o';
            }
            
            free(eliminado);
        }
		
		/*si pide mostrar paso por paso 
		printf("\n Presione enter para continuar....");
		clear_buffer();
		imprimirLab(lab);*/

    }
	
    return pila;
}