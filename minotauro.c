#include <stdlib.h>
#include "minotauro.h"
#include "laberinto.h"
#include "cola.h"


// Crear matriz
int** mat_distancias(int filas, int columnas) {
    int** distancias = malloc(filas * sizeof(int*));
    if (distancias == NULL) {
        return NULL; //memoria filas
    }
for (int i = 0; i < filas; i++) {
    distancias[i] = malloc(columnas * sizeof(int));
    if (distancias[i] == NULL) { 
        return NULL;
} //memoria columnas
for (int j = 0; j < columnas; j++) {
    distancias[i][j] = -1;
    }
}

return distancias; 
}

void liberar(int** distancias, int filas) {
    for (int i = 0; i < filas; i++) {
        free(distancias[i]);
    }
    free(distancias);
}

//empezamo el bfs 

Posicion mino_next_step(Laberinto* lab, Posicion posMi, Posicion posTe) {
    int** distancias = mat_distancias(lab->filas, lab->columnas);
    if(distancias == NULL) {
        return posMi; 
}

Cola* cola_act = cola_crear();
if (cola_act == NULL) {
    return posMi;
}

distancias[posTe.fila][posTe.columna] = 0; //la ubicacion de teseo es el "origen"
cola_encolar(cola_act, posTe);

while (!cola_vacia(cola_act)) {
    Posicion actual = cola_desencolar(cola_act) ; // accion de mantener ubicado a teseo en cada turno

    Direccion direcciones[4] = {ARRIBA, ABAJO, IZQUIERDA, DERECHA};

    for (int i = 0; i < 4; i++){
     Direccion dir = direcciones[i];

        if (moverse_laberinto(lab, actual, dir)) { //confirmar si podemos ir por ahí
            Posicion vecino = laberinto_vecino(actual, dir);
        
            if (distancias[vecino.fila][vecino.columna] == -1) {
                distancias[vecino.fila][vecino.columna] = distancias[actual.fila][actual.columna] + 1;
                cola_encolar(cola_act, vecino);
            }
        }
    }
}

//ahroa si s emueve i think
Posicion movestart = posMi;

int min_distancia =  999999;

Direccion dirs_mino[4] = {ARRIBA, ABAJO, IZQUIERDA, DERECHA};

for(int i = 0; i < 4; i++) { 
    Direccion dir = dirs_mino[i];
    if(moverse_laberinto(lab, posMi, dir)) {
        Posicion vecino = laberinto_vecino(posMi, dir);
        int dist_vecino = distancias[vecino.fila][vecino.columna];

        if (dist_vecino != -1 && dist_vecino < min_distancia) {
           min_distancia = dist_vecino;
           movestart = vecino;
        }
    }
}

cola_destruir(cola_act);
liberar (distancias, lab ->filas);

return movestart;
}