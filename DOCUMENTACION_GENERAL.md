# Documentación General — Theseus-Escape

**Proyecto:** Simulación del Laberinto de Creta (Teseo, el Minotauro y los rehenes)

## Resumen del proyecto

El proyecto parte de una adaptación entre los miembros del Mito del Minotauro, nuestra versión tendremos a Teseo, como el jugador, quien dentro del laberinto de Creta debe restacar a los rehenes repartidos en el laberinto mientras evita ser atrapado por el Minotauro. Esta planeado como un juego por turnos en consola donde Teseo (jugador) debe moverse entre las distintas celdas del laberinto rescatando a cada rehen, mientras que el Minotauro lo persigue por medio del algoritmo (BFS). Cada movimiento representa un turno entre Teseo y el Minotauro hasta que se cumpla la condición de victoria o derrota.

**Condición de victoria:** Rescatar a todos los rehenes.
**Condición de derrota:** Ser atrapado por el Minotauro.

## Estructura del proyecto
Se presenta una organización modular con separación clara de responsabilidades:

| Módulo | Responsabilidad |
|:-------- |:--------:|
| cola.h/c     | TAD para la cola (FIFO) y soporte del BFS  |
| laberinto.h/c     | Representación y generación del laberinto, y consultas de movimientos   |
| minotauro.h/c     | IA de persecusión mediante BFS   |
| teseo.h/c     | Estado del jugador, movimiento y lógica de rescate/victoria   |
| ui.c     | Renderizado del laberinto en la terminal
| main.c     | Bucle principal del juego orquestado por turnos   |