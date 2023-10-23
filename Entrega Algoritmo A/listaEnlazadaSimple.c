#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "listaEnlazadaSimple.h"


int
crearVacia(ListaEnlazadaRef raiz)
{
	*raiz = NULL; 
}


int
estaVacia(ListaEnlazada raiz)
{
	return (raiz == NULL); 
}


tipoNodoRef
creaNodo(tipoInfoRef info)
{
	tipoNodoRef nuevo;
	nuevo = (tipoNodoRef) malloc(sizeof(tipoNodo));
	if(nuevo != NULL){
		nuevo->info = *info;
		nuevo->sig = NULL;
		return (nuevo);
	}else{
		puts("Fallo en la creaciÃ³n de un nuevo nodo.\n");
		return (nuevo);
	}
	
}


int
insertarDespuesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info)
{
	tipoNodoRef aux, nuevo;
	if((nuevo = creaNodo(info)) == NULL){
		puts("Error en la reserva de memoria.\n");
		return -1;	
	}else{
		if(estaVacia(*raiz)){
			*raiz = nuevo;
		}else if(pos == NULL){
			aux = *raiz;
			while(aux->sig != NULL){
				aux = aux->sig;
			}
			aux->sig = nuevo;
		}else{
			aux = *raiz;
			while (aux != NULL && aux != pos){
				aux = aux->sig;			
			}
			if(aux != NULL){
				nuevo->sig = pos->sig;
				pos->sig = nuevo;
			}else{
				free(nuevo);
				puts("ERROR : posiciÃ³n inexistente introducida.\n");
				return -2;
			}			
		}
		
	}	return 0;
 }


int
insertarAntesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info) 
{
	tipoNodoRef nuevo, ant;
	 
	if(NULL == (nuevo = creaNodo(info))){
		puts("Erroe en reserva de memoria.\n");	return -1;
	} 
	if(estaVacia(*raiz) || pos == NULL || pos == *raiz){
		nuevo->sig = *raiz;
		*raiz = nuevo;
	}else{
		ant = *raiz;
		while(ant->sig != pos){
			ant = ant->sig;
		}
		nuevo->sig = pos;
		ant->sig = nuevo;
		
	}
	return 0;
}




int
insertarNodoComienzo(ListaEnlazadaRef raiz, tipoInfoRef info)
{
	return (insertarAntesDeNodo(raiz,*raiz,info));
}


int
liberarListaEnlazada(ListaEnlazadaRef raiz)
{
	tipoNodoRef aux, aBorrar;
	if(estaVacia(*raiz)){
		puts("¡La lista introducida está vacía!\n");
		exit (-1);
	}
	aux = *raiz;
	while(aux != NULL){
		aBorrar = aux;
		aux = aux->sig;
		free(aBorrar);
	}
	//puts("Lista Liberada.\n");
	return 0;
}

int insertarOrdenada(ListaEnlazadaRef raiz, tipoInfoRef info, int valor_funcion_heuristica)
{
    int errNum;
    tipoNodo *aux;
    aux = *raiz;
    if (raiz == NULL)
    {
        errNum = insertarAntesDeNodo(raiz, aux, info);
    }
    else
    {
        while (aux != NULL && aux->info.valor_funcion_heuristica < valor_funcion_heuristica)
        {
              aux = aux->sig;
        }
        if (aux == NULL)
        {
              errNum = insertarDespuesDeNodo(raiz, aux, info);
        }
        else
        {
              errNum = insertarAntesDeNodo(raiz, aux, info);
        }
    }
    return errNum;
}

int
mostrarListaEnlazada(ListaEnlazada raiz)
{
	tipoNodoRef aImprimir;
	int res = 0,i = 0;
	
	printf("\n\n");
	printf("%-14s%-10s\n","  Posicion", "Valor");
	printf("%-14s%-10s\n","  ==========", "======");


	aImprimir = raiz;
	while (aImprimir != NULL) {
		printf("\t%d)\t(%d, %d, %d) [%d]\n",i++, aImprimir->info.x, aImprimir->info.y, aImprimir->info.a, aImprimir->info.valor_funcion_heuristica);
		aImprimir = aImprimir->sig;
	}
	return res;
}

tipoNodoRef
extraePrimerNodo(ListaEnlazadaRef raiz, ListaEnlazadaRef raiz2)
{
	tipoNodoRef aux;
	
	aux = *raiz;
	*raiz = aux->sig;

	aux->sig = *raiz2;
	*raiz2 = aux;

	return aux;
}

int
buscarEstadoListaEnlazada(ListaEnlazada raiz, tipoInfoRef pos)
{
	tipoNodoRef aux;

	aux = raiz;
	while (aux != NULL) {
		if (aux->info.x == pos->x && aux->info.y == pos->y && aux->info.a == pos->a) {
			return 1;
		}		
		aux = aux->sig;
	}
	return 0;
}

void crearArbolVacio(tipoNodoArbolBusqueda * arbol) {
	for (int i = 0; i < TAM_ARBOL; i++) {
		arbol[i].n = 0;
		arbol[i].profundidad = 0;
	
		arbol[i].estado.x = 0; 
		arbol[i].estado.y = 0;
		arbol[i].estado.a = 0;
		
		arbol[i].heuristica.f = 0;
		arbol[i].heuristica.h = 0;
		arbol[i].heuristica.g = 0;
	}
}

int calcularProfundidadNodoArbol(tipoNodoArbolBusqueda * arbol, int indice_nodo) {
	if (arbol[indice_nodo].n == 0) {
		return 1;
	}
	else {
		return 1 + calcularProfundidadNodoArbol(arbol, arbol[indice_nodo].n);
	}
	
}

void ajustarApuntadores(tipoNodoArbolBusqueda * arbol, tipoInfo estado, int indice_padre, int cerrado) {
	int indice_arbol;
	
	for (int i = 1; i < TAM_ARBOL; i++) {
		if (arbol[i].estado.x == estado.x && arbol[i].estado.y == estado.y && arbol[i].estado.a == estado.a) {
			indice_arbol = i;
			break;
		}
	}
			
	if (calcularProfundidadNodoArbol(arbol, indice_padre) + 1 < arbol[indice_arbol].profundidad) {
		arbol[indice_arbol].profundidad = calcularProfundidadNodoArbol(arbol, indice_padre) + 1;
		arbol[indice_arbol].n = indice_padre;
		
	}
	
	if (cerrado == 1) {
		for (int i = 1; i < TAM_ARBOL; i++) {
			if (arbol[i].n == indice_arbol) {
				ajustarApuntadoresDescendientes(arbol, i, indice_arbol);				
			}
		}		
	}
}

void ajustarApuntadoresDescendientes(tipoNodoArbolBusqueda * arbol, int indice_arbol, int indice_padre) {
	if (calcularProfundidadNodoArbol(arbol, indice_padre) + 1 < arbol[indice_arbol].profundidad) {
		arbol[indice_arbol].profundidad = calcularProfundidadNodoArbol(arbol, indice_padre) + 1;
		arbol[indice_arbol].n = indice_padre;
	}
	
	for (int i = 1; i < TAM_ARBOL; i++) {
		if (arbol[i].n == indice_arbol) {
			ajustarApuntadoresDescendientes(arbol, i, indice_arbol);		
		}
	}
	
}


int hayParedVertical(int xinicial, int y, int xfinal) {

	if (xinicial == 1 && xfinal == 2 && y == 2) {
		return 1;
	}
	if (xinicial == 1 && xfinal == 2 && y == 5) {
		return 1;
	}
	if (xinicial == 2 && xfinal == 3 && y >= 3 && y <= 4) {
		return 1;
	}
	if (xinicial == 3 && xfinal == 4 && y == 2) {
		return 1;
	}
	if (xinicial == 3 && xfinal == 4 && y == 4) {
		return 1;
	}
	if (xinicial == 4 && xfinal == 5 && y >= 1 && y <= 3) {
		return 1;
	}
	if (xinicial == 5 && xfinal == 6 && y >= 2 && y <= 3) {
		return 1;
	}
	if (xinicial == 6 && xfinal == 7 && y >= 2 && y <= 5) {
		return 1;
	}
	return 0;
}

int hayParedHorizontal(int yinicial, int x, int yfinal) {
	if (yinicial == 2 && yfinal == 3 && x >= 2 && x <= 3) {
		return 1;
	}
	if (yinicial == 3 && yfinal == 4 && x == 1) {
		return 1;
	}
	if (yinicial == 3 && yfinal == 4 && x >= 4 && x <= 5) {
		return 1;
	}
	if (yinicial == 4 && yfinal == 5 && x == 2) {
		return 1;
	}
	if (yinicial == 4 && yfinal == 5 && x >= 4 && x <= 5) {
		return 1;
	}	
	return 0;
}


int colaCreaVacia(Cola *c)
{
    c->frente = NULL;      
    c->fondo = NULL; 
    return 0;
}

int colaVacia(Cola *c)
{
    if (c->frente == NULL && c->fondo == NULL) {
        return 1;
    }
    else {
        return 0;
    }       
}

int colaInserta(Cola *c,tipoInfo elemento)
{
    tipoCelda *nuevo;
    nuevo = (tipoCelda *)malloc(sizeof(tipoCelda));
    if (nuevo == NULL) {
        return -1;
    }
    else {
        if (colaVacia(c) == 1) {
            c->frente = nuevo;
            nuevo->elemento = elemento;
            nuevo->sig = NULL;
            c->fondo = nuevo;
        }
        else {
            nuevo->elemento = elemento;
            nuevo->sig = NULL;
            c->fondo->sig = nuevo;
            c->fondo = nuevo;
        }
        return 0;
    }         
}

tipoInfo colaSuprime(Cola *c)
{
    tipoCelda *suprimir;
    tipoInfo elemento;
    if (colaVacia(c) == 1) {
        return elemento;
    }
    if (c->frente == c->fondo) { //si solo queda un nodo (se cumple que el frente y el fondo son iguales) antes de eliminarlo ponemos fondo a null
        c->fondo = NULL;
    }
    suprimir = c->frente;
    elemento = suprimir->elemento;
    c->frente = suprimir->sig;
    free(suprimir);
    return elemento;      
}

 
 
