#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include "listaEnlazadaSimple.h"

int main(int argc, const char * argv[])
{
	ListaEnlazada conjunto_abiertos, conjunto_cerrados;
	tipoInfo estado_inicial, estado_final;
	tipoNodo * nodo;
	tipoInfo estado_expandido1, estado_expandido2, estado_expandido3, estado_expandido;
	int indice_padre = 1, level = 1;
	tipoNodoArbolBusqueda arbol[TAM_ARBOL];
	Cola c;
	
	colaCreaVacia(&c); //creamos una cola inicialmente vacia, para almacenar en esta cola los estados expandidos M
	
	crearArbolVacio(arbol); //creamos el arbol de busqueda, inicialmente vacio
	
	crearVacia(&conjunto_abiertos); //creamos el conjunto de estados abiertos, inicialmente vacio
	crearVacia(&conjunto_cerrados); //creamos el conjunto de estados cerrados, inicialmente vacio
	
	
	//DEFINICION DEL ESTADO INICIAL
	estado_inicial.x = 1;
	estado_inicial.y = 4;
	estado_inicial.a = 0;
	
	//DEFINICION DEL ESTADO FINAL
	estado_final.x = 7;
	estado_final.y = 4;
	estado_final.a = 0;
	
	insertarNodoComienzo(&conjunto_abiertos, &estado_inicial); //añadimos el estado inicial al conjunto de estados abiertos
	
	//AÑADIMOS AL ARBOL DE BUSQUEDA EL ESTADO INICIAL CON LA INFORMACION CORRESPONDIENTE
	
	arbol[1].estado = estado_inicial;
	arbol[1].profundidad = 1;
	arbol[0].n = arbol[0].n + 1;
	
	int distancia = 0;
	
	distancia = fabs((estado_final.x - estado_inicial.x)) + fabs((estado_final.y - estado_inicial.y));
	
	arbol[1].heuristica.h = distancia;
	arbol[1].heuristica.g = 0;
	arbol[1].heuristica.f = arbol[1].heuristica.h + arbol[1].heuristica.g;
		
	while (!estaVacia(conjunto_abiertos)) { //mientras el conjunto de abiertos no este vacio, iteramos			
		nodo = extraePrimerNodo(&conjunto_abiertos, &conjunto_cerrados); //extraemos el primer nodo de la lista de abiertos y lo añadimos a la lista de cerrados
				
		for (int i = 0; i < TAM_ARBOL; i++) { //obtencion del indice en el que se encuentra el estado extraido en el arbol
			if (arbol[i].estado.x == nodo->info.x && arbol[i].estado.y == nodo->info.y && arbol[i].estado.a == nodo->info.a) {
				indice_padre = i;
				break;
			}
		}
		
		if (nodo->info.x == 7 && nodo->info.y == 4 && nodo->info.a == 0) { //revisamos si el nodo expandido se trata del estado o nodo final
			printf("\nSolucion encontrada con exito!!!\n");
			break;
		}
				
		//EXPANSION DEL NODO
			
		//APLICACION DE LA REGLA AVANZAR (TENIENDO EN CUENTA LA ORIENTACION)
		switch (nodo->info.a) {
			case 0:
				if (hayParedVertical(nodo->info.x, nodo->info.y, nodo->info.x + 1) == 0 && nodo->info.x < 7) { //comprobamos que no hay pared delante y que nos matenemos en el recinto del labertinto antes de aplciar esta regla y expandir el nodo correspondiente
					estado_expandido1.x = nodo->info.x + 1;
					estado_expandido1.y = nodo->info.y;
					estado_expandido1.a = nodo->info.a;
					colaInserta(&c, estado_expandido1); //insertamos el estado expandido a la cola
				}
				break;
			case 1:
				if (hayParedHorizontal(nodo->info.y, nodo->info.x, nodo->info.y + 1) == 0 && nodo->info.y < 6) { //comprobamos que no hay pared delante y que nos matenemos en el recinto del labertinto antes de aplciar esta regla y expandir el nodo correspondiente
					estado_expandido1.y = nodo->info.y + 1;
					estado_expandido1.x = nodo->info.x;
					estado_expandido1.a = nodo->info.a;
					colaInserta(&c, estado_expandido1); //insertamos el estado expandido a la cola
				}
				break;
			case 2:
				if (hayParedVertical(nodo->info.x - 1, nodo->info.y, nodo->info.x) == 0 && nodo->info.x > 1) { //comprobamos que no hay pared delante y que nos matenemos en el recinto del labertinto antes de aplciar esta regla y expandir el nodo correspondiente
					estado_expandido1.x = nodo->info.x - 1;
					estado_expandido1.y = nodo->info.y;
					estado_expandido1.a = nodo->info.a;
					colaInserta(&c, estado_expandido1); //insertamos el estado expandido a la cola
				}
				break;
			case 3:
				if (hayParedHorizontal(nodo->info.y - 1, nodo->info.x, nodo->info.y) == 0 && nodo->info.y > 1) { //comprobamos que no hay pared delante y que nos matenemos en el recinto del labertinto antes de aplciar esta regla y expandir el nodo correspondiente
					estado_expandido1.y = nodo->info.y - 1;
					estado_expandido1.x = nodo->info.x;
					estado_expandido1.a = nodo->info.a;
					colaInserta(&c, estado_expandido1); //insertamos el estado expandido a la cola
				}
				break;				
		}	

		//APLICACION DE LA REGLA DE GIRO A LA DERECHA		
		estado_expandido2.x = nodo->info.x;
		estado_expandido2.y = nodo->info.y;
		
		if (nodo->info.a == 3) {
			estado_expandido2.a = 0;
		}
		else {
			estado_expandido2.a = nodo->info.a + 1;
		}

		colaInserta(&c, estado_expandido2); //insertamos el estado expandido a la cola
		
		//APLICACION DE LA REGLA DE GIRO A LA IZQUIERDA
		estado_expandido3.x = nodo->info.x;
		estado_expandido3.y = nodo->info.y;
		
		if (nodo->info.a == 0) {
			estado_expandido3.a = 3;
		}
		else {
			estado_expandido3.a = nodo->info.a - 1;
		}

		colaInserta(&c, estado_expandido3); //insertamos el estado expandido a la cola
		
		//Extración del conjunto de estados sucesores M
		
		while (colaVacia(&c) == 0) { //se extraen todos los estados expandidos y para cada uno se realiza las acciones necesarias en funcion de si el estado expandido ya estaba en abiertos o en cerrados
			estado_expandido = colaSuprime(&c);
			
			if (buscarEstadoListaEnlazada(conjunto_abiertos, &estado_expandido)) { //si el estado expandido ya estaba en abiertos, se revisa el apuntador de este nodo expandido			
				ajustarApuntadores(arbol, estado_expandido, indice_padre, 0);				
			}
			else if (buscarEstadoListaEnlazada(conjunto_cerrados, &estado_expandido)) {//si el estado expandido ya estaba en cerrados, se revisa el apuntador de este nodo expandido y el de sus descendientes					
				ajustarApuntadores(arbol, estado_expandido, indice_padre, 1);
			}
			else { //si el estado expandido no estaba ni en abiertos ni en cerrados, se añade este nodo al arbol y se establece su correspodiente apuntador al padre
				arbol[arbol[0].n + 1].estado = estado_expandido;
				arbol[arbol[0].n + 1].n = indice_padre;
				arbol[arbol[0].n + 1].profundidad = arbol[indice_padre].profundidad + 1;
				
				distancia = fabs((estado_final.x - estado_expandido.x)) + fabs((estado_final.y - estado_expandido.y));
				//distancia = fabs((estado_final.x - estado_expandido.x)) + (((estado_expandido.y - estado_final.y) + 4) * 20);
				
				/*if (estado_expandido.x > 5) {
					distancia = fabs((estado_final.x - estado_expandido.x)) + (((estado_expandido.y - estado_final.y) + 4) * 20);
				}
				else {
					distancia = fabs((estado_final.x - estado_expandido.x)) + fabs((estado_final.y - estado_expandido.y));
				}*/
				
				arbol[arbol[0].n + 1].heuristica.h = distancia;
				arbol[arbol[0].n + 1].heuristica.g = level;
				arbol[arbol[0].n + 1].heuristica.f = arbol[arbol[0].n + 1].heuristica.h + arbol[arbol[0].n + 1].heuristica.g;
				estado_expandido.valor_funcion_heuristica = arbol[arbol[0].n + 1].heuristica.f;
				
				arbol[0].n = arbol[0].n + 1;
				
				
				insertarOrdenada(&conjunto_abiertos, &estado_expandido, arbol[arbol[0].n].heuristica.f); //se inserta este estado expandido en abiertos y se ordena en funcion de la heurisitca que hemos definido
			}
		}
		
		level++;					
	}
	
	//PRESENTACION DE LA SOLUCION
	
	int indice_final;
	for (int i = 1; i < TAM_ARBOL; i++) { //obtenemos el indice en el arbol en el que se encuentra el estado final para reconstruir la serie de estados hasta alcanzar la solucion
		if (arbol[i].estado.x == 7 && arbol[i].estado.y == 4 && arbol[i].estado.a == 0) {
			indice_final = i;
			break;
		}
	}
	
	printf("\nSe han explorado %d estados\n", indice_final);
	
	printf("\n\n");
	
	while (arbol[indice_final].n != 0) { //recorremos los apuntadores desde el estado final para obtener la secuencia de estados que forman parte de la solucion
		printf("%d (%d, %d, %d)\n", arbol[indice_final].n, arbol[indice_final].estado.x, arbol[indice_final].estado.y, arbol[indice_final].estado.a);			
		indice_final = arbol[indice_final].n;
	}
	
	printf("%d (%d, %d, %d)\n", arbol[indice_final].n, arbol[indice_final].estado.x, arbol[indice_final].estado.y, arbol[indice_final].estado.a);
	printf("\n\n");

	liberarListaEnlazada(&conjunto_abiertos);
	liberarListaEnlazada(&conjunto_cerrados);
	
    return 0;
}
