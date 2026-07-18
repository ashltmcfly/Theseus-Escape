# Documentación General — Theseus-Escape

**Proyecto:** Simulación del Laberinto de Creta (Teseo, el Minotauro y los rehenes)

## Resumen del proyecto

El proyecto parte de una adaptación del Mito del Minotauro. En nuestra versión, tendremos a Teseo como el jugador y quien, estando dentro del Laberinto de Creta, debe restacar a tres rehenes repartidos en el laberinto mientras evita ser atrapado por el Minotauro. Está planteado como un juego por turnos en consola donde Teseo (jugador) debe moverse entre las distintas celdas del laberinto rescatando a cada rehén, mientras que el Minotauro lo persigue por medio del algoritmo (BFS). Cada movimiento representa un turno entre Teseo y el Minotauro hasta que se cumpla la condición de victoria o derrota.

**Condición de victoria:** Rescatar a todos los rehenes.
**Condición de derrota:** Ser atrapado por el Minotauro.

## Estructura del proyecto
Se presenta una organización modular con separación de responsabilidades:

| Módulo | Responsabilidad |
|:-------- |:--------:|
| cola.h/c     | TAD para la cola (FIFO) y soporte del BFS  |
| laberinto.h/c     | Representación y generación del laberinto, y consultas de movimientos   |
| minotauro.h/c     | IA de persecusión mediante BFS   |
| teseo.h/c     | Estado del jugador, movimiento y lógica de rescate/victoria   |
| ui.c     | Renderizado del laberinto en la terminal
| main.c     | Bucle principal del juego orquestado por turnos   |