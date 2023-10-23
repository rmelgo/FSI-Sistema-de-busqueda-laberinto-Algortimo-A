#ifndef LISTA_ENLAZADA_SIMPLE_H
#define LISTA_ENLAZADA_SIMPLE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_ARBOL 200

//Definicion de tipos para las listas enlazadas (conjunto de abiertos y de cerrados)

typedef struct tipoInfo {
	int x;
	int y;				
	int a;
	int valor_funcion_heuristica;
} tipoInfo;

typedef tipoInfo *tipoInfoRef;

typedef struct tipoNodo {
	tipoInfo info;				
	struct tipoNodo * sig;
} tipoNodo;
typedef tipoNodo *tipoNodoRef;

typedef tipoNodo * ListaEnlazada;
typedef ListaEnlazada *ListaEnlazadaRef;

//Definicion de tipos para el arbol de busqueda

typedef struct tipoHeuristica {
	int f;
	int h;				
	int g;
} tipoHeuristica;

typedef struct tipoNodoArbolBusqueda {
	int n;
	int profundidad;
	tipoInfo estado;
	tipoHeuristica heuristica;
} tipoNodoArbolBusqueda;

//Definicion de tipos para las colas

typedef struct tipoCelda {
	tipoInfo elemento;
	struct tipoCelda * sig;
	} tipoCelda;

typedef struct {
        tipoCelda *frente, *fondo;
} Cola;




//Funciones basicas de listas enlazadas

int crearVacia(ListaEnlazadaRef raiz);
int estaVacia(ListaEnlazada raiz);
tipoNodoRef creaNodo(tipoInfoRef info);
int insertarDespuesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info);
int insertarAntesDeNodo(ListaEnlazadaRef raiz, tipoNodoRef pos, tipoInfoRef info);
int insertarNodoComienzo(ListaEnlazadaRef raiz, tipoInfoRef info);
int liberarListaEnlazada(ListaEnlazadaRef raiz);


//Funciones avanzadas de listas enlazadas

int insertarOrdenada(ListaEnlazadaRef raiz, tipoInfoRef info, int valor_funcion_heuristica);
int mostrarListaEnlazada(ListaEnlazada raiz);
tipoNodoRef extraePrimerNodo(ListaEnlazadaRef raiz, ListaEnlazadaRef raiz2);
int buscarEstadoListaEnlazada(ListaEnlazada raiz, tipoInfoRef pos);

//Funciones relativas al algortimo A* y a la resolucion de nuestro problema

void crearArbolVacio(tipoNodoArbolBusqueda * arbol);
int calcularProfundidadNodoArbol(tipoNodoArbolBusqueda * arbol, int indice_nodo);
void ajustarApuntadores(tipoNodoArbolBusqueda * arbol, tipoInfo estado, int indice_padre, int cerrado);
void ajustarApuntadoresDescendientes(tipoNodoArbolBusqueda * arbol, int indice_arbol, int indice_padre);
int hayParedVertical(int xinicial, int y, int xfinal);
int hayParedHorizontal(int yinicial, int x, int yfinal);

//Funciones para el manejo de las colas

int colaCreaVacia(Cola *c);
int colaVacia(Cola *c);
int colaInserta(Cola *c, tipoInfo elemento);
tipoInfo colaSuprime(Cola *c);

#endif


