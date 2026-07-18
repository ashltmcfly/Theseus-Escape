# Documentación Técnica — Theseus-Escape

**Proyecto:** Simulación del Laberinto de Creta (Teseo, el Minotauro y los rehenes)

## Estructuras utilizadas:
**Posición:** Estructura (fila, columna) usado como el tipo de dato para manejar en la cola y demás modulos del proyecto, en el formato de posiciones como un unico valor dado el uso de matrices para la base.
**Celda:** Estructura auxiliar para el diseño de una pared como la casilla de la matriz con sus cuatro direcciones junto a un dato adicional de si ha sido visitada o no.
**Laberinto:** Estructura base bajo el diseño de una matriz dinámica como el arreglo de punteros a filas en formato de la estructura Celda.
**Cola:** Estructura auxiliar para el uso del BFS.
**Teseo_Estado:** Estructura agrupadora de la posición del jugador, posiciones de los rehenes, arreglo de rehenes rescatados y un contador.


## Algoritmos utilizados:
**Generación del laberinto — DFS recursivo con backtracking:** Se usa el DFS dada su aplicación de inmersión profunda dentro de la matriz para diseñar primero la ruta perfecta desde la posición inicial hasta la final de forma aleatoria sin repetir. El uso del backtracking queda para la recursión de regresar a una casilla anterior hasta tomar otro camino una vez se agoten los vecinos de la celda actual. Como extra se tiene una función para abrir paredes en el laberinto perfecto creado por el DFS con el fin de tener mayores opciones de rutas disponibles.
**Persecución del Minotauro — BFS:** Se usa para obtener la cantidad de celdas más óptimas desde la posición del Minotauro hasta la posición de Teseo por medio de una inspección a cada uno de sus 4 posibles celdas vecinas, con el fin de moverse en dicha dirección.

## Decisiones de diseño:
**Uso de DFS para la generación del laberinto:** Al usar la excavación del DFS con direccionamiento aleatorio se logra obtener un primer laberinto perfecto donde todas las casillas son alcanzables conectando todas las partes del laberinto.
**Apertura de ciclos para jugabilidad:** Para evitar problemas de tener una sola ruta posible dado el laberinto perfecto, de forma aleatoria según cierto porcentaje se inspecciona el laberinto y se abren diversas celdas (paredes) del mismo generando nuevas opciones de rutas.
**Uso de BFS para la ruta más óptima hacia Teseo:** El BFS parte del objetivo (Teseo) y no del perseguidor (Minotauro), llenando una matriz de distancias donde cada celda indica cuántos pasos faltan para llegar a Teseo. El Minotauro solo compara sus 4 vecinos y pisa el de menor valor. Esto evita reconstruir el camino con una matriz de predecesores. Además el uso de BFS en lugar de otros algoritmos similares se debe principalmente a que se maneja un grafo ponderado
**