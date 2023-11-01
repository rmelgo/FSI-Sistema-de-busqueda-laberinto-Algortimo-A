# Implementación de un algoritmo A* para resolver un laberinto

![inicio](https://github.com/rmelgo/FSI-Sistema-de-busqueda-laberinto-backtrack/assets/145989723/763abf67-044f-4690-ae5e-e3d5bc6576c6)

# - Introducción

Proyecto realizado en la asignatura de ***Fundamentos de Sistemas Inteligentes*** del grado de Ingenieria Informática de la Universidad de Salamanca. El enunciado del proyecto se encuentra subido en el repositorio en un archivo PDF llamado <a href="https://github.com/rmelgo/FSI-Sistema-de-busqueda-laberinto-backtrack/blob/main/Pra%CC%81cticaBu%CC%81squedaLaberinto.pdf" target="_blank">*PrácticaBúsquedaLaberinto.pdf*</a>.

El principal objetivo de este proyecto es la realización de un programa que implemente el algoritmo A* para que un robot pueda resolver un laberinto. 

Especificaciones básicas del problema:

- El robot cuenta con un sensor de posición que permite saber en que posición del laberinto se encuentra y un sensor de choque que permite detectar las paredes del laberinto.
- El robot unicamente cuenta con movimiento de avance y giro de 90 grados hacia derecha e izquierda.

Para implementar el algoritmo A*, se ha utilizado el lenguaje C ya que son necesarias ciertas estructuras de datos como colas, listas enlazadas y árboles las cuales ya han sido implementadas previamente.

# - Comentarios sobre el entorno de ejecución

Para ejecutar este programa, se requerirá de una distribución del Sistema Operativo **GNU/Linux**, aunque también se puede ejecutar en **Windows**.    

Para poder compilar correctamente el programa, se deberá tener instalada una versión del compilador gcc o similar. En el caso de no tener gcc, se puede instalar fácilmente con el siguiente comando:

```sudo apt install gcc```

# Comentarios sobre el material adjuntado

El proyecto cuenta con los siguientes ficheros:

- Una carpeta llamada ***Entrega_Algoritmo_A*** que contendrá los ficheros en los cuales se implementará el algoritmo A* para resolver el laberinto. Dentro de esta carpeta, existen 3 ficheros:
 
  - Un fichero llamado ***main.c*** que contiene la implementación del algoritmo A* para la resolución del laberinto. Este código hace uso de funciones auxiliares que se encuentran en otro fichero.
  - Un fichero llamado ***listaEnlazadaSimple.c*** que contiene las funciones necesarias para implementar las funciones básicas de las distintas estructuras de datos (listas enlazadas, colas y árboles) necesarias para la implementación del algoritmo A*.
  - Un fichero llamado ***listaEnlazadaSimple.h*** que contiene las cabeceras de las funciones definidas en *listaEnlazadaSimple.c* así como una serie de tipos de datos que se utilizan para implementar las distintas estructuras de datos.
      
- Un documento llamado ***Práctica de Sistemas de Búsqueda.pdf*** que contiene una especificación formal del problema del laberinto así como pruebas de la resolución del laberinto utilizando las 2 versiones del algortimo de backtracking.

# Conceptos teóricos (Diferencia entre algortimo A vs Algoritmo A*)

La implementación de un *algoritmo A* y la implementación de un *algortimo A** para la resolución de un problema es muy similar. Ambas implementaciones buscan expandir una serie de estados hasta encontrar una solución al problema.

La diferencia radica en que el *algorirtmo A** utiliza una heurística admisible del problema para ordenar lo que se llama el conjunto de estados abiertos (conjunto de estados que se van a expandir) mientras que el *algoritmo A* no utiliza este criterio.

Una **heurística admisible** es aquella que no sobreestima el esfuerzo necesario para llegar a la solución óptima.

De esta manera, la implementación de un *algoritmo A* garantiza la obtención de la solución óptima mientras que implementación de un *algortimo A** no garantiza dar con la solución óptima.

En el caso particular de este problema, una heurística admisible es la utilización de la ***distancia Manhattan***. La distancia Manhattan se calcula sumando la diferencia en valor absoluto de componente x del estado actual y el final más la diferencia en valor absoluto de componente y del estado actual y el final. 

![heuristica](https://github.com/rmelgo/FSI-Sistema-de-busqueda-laberinto-Algortimo-A/assets/145989723/b41acff0-b0ad-40e4-8378-96c1c76148a2)

Con esta heurística, no se sobreestima el esfuerzo necesario para llegar a la solución óptima ya que se necesitan como mínimo tantos movimientos como distancia Manhattan haya entre el punto actual y la salida del laberinto, por lo tanto, es una heurística admisible.

# - Pasos necesarios para ejecutar el programa

**Paso 1: Compilar el programa**  

Para ello, se debe introducir el siguiente comando:    

```gcc listaEnlazadaSimple.c -o listaEnlazadaSimple```

**Paso 2: Ejecutar el programa**  

Para ello, se debe introducir el siguiente comando:    

```./clistaEnlazadaSimple```

Tras ejecutar este comando, el programa se habra ejecutado correctamente.

# - Ejemplo de ejecución

## Algoritmo A*

En la siguiente imagen, se muestra un ejemplo del uso y funcionamiento de la implementación del *algoritmo A** diseñado para resolver el problema del laberinto:

![Ejemplo ejecucion 1](https://github.com/rmelgo/FSI-Sistema-de-busqueda-laberinto-Algortimo-A/assets/145989723/4d3b365b-7775-4171-a6c7-84f73c1dffe1)

El recorrido obtenido que debe seguir el robot para alcanzar la salida del laberinto es el siguiente:

![Ejemplo ejecucion 2](https://github.com/rmelgo/FSI-Sistema-de-busqueda-laberinto-Algortimo-A/assets/145989723/af2c4dbc-8f8a-469d-bdbe-8e40c0ca2f1b)

Como se puede observar, se han explorado 97 hasta encontrar la solución del laberinto. Al utilizar una implementación del *algortimo A** con una heurística admisible, la solución obtenida es óptima con total seguridad.

## Algoritmo A

Ahora, para cambiar la implementación del *algortimo A** a una implementación del *algoritmo A*, simplemente hay que cambiar la heurística admisible por una no admisible. 

Para ello, simplemente se debe comentar la línea 145 de ***main.c*** y descomentar a línea 146 de ***main.c*** que contiene una heurística no admisible.

En la siguiente imagen, se muestra un ejemplo del uso y funcionamiento de la implementación del *algoritmo A* diseñado para resolver el problema del laberinto:

![Ejemplo ejecucion 3](https://github.com/rmelgo/FSI-Sistema-de-busqueda-laberinto-Algortimo-A/assets/145989723/668150d8-4905-4956-93a7-4d3ab3012bf4)

El recorrido obtenido que debe seguir el robot para alcanzar la salida del laberinto es el siguiente:

![Ejemplo ejecucion 4](https://github.com/rmelgo/FSI-Sistema-de-busqueda-laberinto-Algortimo-A/assets/145989723/954fa479-dc0d-4731-a060-2bc0a886c020)

Como se puede observar, se han explorado 133 hasta encontrar la solución del laberinto. Al utilizar una implementación del *algortimo A* con una heurística no admisible, la solución obtenida no se puede garantizar que es óptima. 
De hecho, en este caso, se ha modificado la heurística intencionadamente para priorizar la búsqueda por la parte superior y encontrar una solución no óptima.

# Conclusiones y resultados

El laberinto cuenta con 6 casillas de altura y 7 casillas de anchura lo que proporciona un total de 42 casillas. Cada casilla cuenta con 4 orientaciones posibles por lo que existen 4x7x6=168 estados distintos.

De esta manera, la implementación del *algortimo A** necesito explorar 97 estados para encontrar la solución mientras que la implementación del *algortimo A* necesito explorar 133 para encontrar la solución.

Se puede observar como implementación del *algortimo A** necesita explorar una **menor** cantidad de estados que el *algortimo A* y además de garantizar que la solución encontrada es óptima.

# - Participantes

<table>
  <td align="center"><a href="https://github.com/rmelgo"><img src="https://avatars.githubusercontent.com/u/145989723?s=400&u=e5c06adba3f3c418207178abc845d398b3d5f77f&v=4" width="100px;" alt=""/><br /><sub><b>Raúl Melgosa</b></sub></a><br/> 
</table>
