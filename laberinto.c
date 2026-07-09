#include <stdlib.h>
#include <time.h>
#include "laberinto.h"

Laberinto* crear_laberinto(int filas, int columnas) {
    Laberinto* lab = malloc(sizeof(Laberinto));
    if (lab == NULL) {
        return NULL;
    }

    lab->filas = filas;
    lab->columnas = columnas;

    lab->grilla = malloc(filas * sizeof(Celda*));
    if (lab->grilla == NULL) {
        free(lab);
        return NULL;
    }

    for (int i = 0; i < filas; i++) {
        lab->grilla[i] = malloc(columnas * sizeof(Celda));
        if (lab->grilla[i] == NULL) {
            // Liberar memoria previamente asignada en caso de error
            for (int j = 0; j < i; j++) {
                free(lab->grilla[j]);
            }
            free(lab->grilla);
            free(lab);
            return NULL;
        }

        for (int j = 0; j < columnas; j++) {
            lab->grilla[i][j].pared_arriba = 1;
            lab->grilla[i][j].pared_abajo = 1;
            lab->grilla[i][j].pared_izquierda = 1;
            lab->grilla[i][j].pared_derecha = 1;
            lab->grilla[i][j].visitada = 0;
        }
    }

    return lab;
}

Posicion laberinto_vecino(Posicion pos, Direccion dir) {
    Posicion vecino = pos;
    switch (dir) {
        case ARRIBA:
            vecino.fila--;
            vecino.columna = pos.columna;
            break;
        case ABAJO:
            vecino.fila++;
            vecino.columna = pos.columna;
            break;
        case IZQUIERDA:
            vecino.fila = pos.fila;
            vecino.columna--;
            break;
        case DERECHA:
            vecino.fila = pos.fila;
            vecino.columna++;
            break;
    }
    return vecino;
}

int laberinto_valido(Laberinto* lab, Posicion pos) {
    if (pos.fila < 0 || pos.fila >= lab->filas || pos.columna < 0 || pos.columna >= lab->columnas) {
        return 0; // Posición fuera de los límites
    }
    return 1;
}

void abrir_pared_laberinto(Laberinto* lab, Posicion a, Posicion b) {
    if (b.fila == a.fila - 1 && b.columna == a.columna) {
        lab->grilla[a.fila][a.columna].pared_arriba = 0;
        lab->grilla[b.fila][b.columna].pared_abajo = 0;
    } else if (b.fila == a.fila + 1 && b.columna == a.columna) {
        lab->grilla[a.fila][a.columna].pared_abajo = 0;
        lab->grilla[b.fila][b.columna].pared_arriba = 0;
    } else if (b.fila == a.fila && b.columna == a.columna - 1) {
        lab->grilla[a.fila][a.columna].pared_izquierda = 0;
        lab->grilla[b.fila][b.columna].pared_derecha = 0;
    } else if (b.fila == a.fila && b.columna == a.columna + 1) {
        lab->grilla[a.fila][a.columna].pared_derecha = 0;
        lab->grilla[b.fila][b.columna].pared_izquierda = 0;
    }
}

void cerrar_pared_laberinto(Laberinto* lab, Posicion a, Posicion b) {
    if (b.fila == a.fila - 1 && b.columna == a.columna) {
        lab->grilla[a.fila][a.columna].pared_arriba = 1;
        lab->grilla[b.fila][b.columna].pared_abajo = 1;
    } else if (b.fila == a.fila + 1 && b.columna == a.columna) {
        lab->grilla[a.fila][a.columna].pared_abajo = 1;
        lab->grilla[b.fila][b.columna].pared_arriba = 1;
    } else if (b.fila == a.fila && b.columna == a.columna - 1) {
        lab->grilla[a.fila][a.columna].pared_izquierda = 1;
        lab->grilla[b.fila][b.columna].pared_derecha = 1;
    } else if (b.fila == a.fila && b.columna == a.columna + 1) {
        lab->grilla[a.fila][a.columna].pared_derecha = 1;
        lab->grilla[b.fila][b.columna].pared_izquierda = 1;
    }
}

static void generar_dfs_laberinto(Laberinto* lab, int fila, int columna) {
    lab->grilla[fila][columna].visitada = 1;

    Direccion direcciones[4] = {ARRIBA, ABAJO, IZQUIERDA, DERECHA};
    // Mezclar direcciones al azar
    for (int i = 0; i < 4; i++) {
        int j = rand() % 4;
        Direccion temp = direcciones[i];
        direcciones[i] = direcciones[j];
        direcciones[j] = temp;
    }

    for (int i = 0; i < 4; i++) {
        Posicion actual = {fila, columna};
        Posicion vecino = laberinto_vecino(actual, direcciones[i]);
        if (laberinto_valido(lab, vecino) && !lab->grilla[vecino.fila][vecino.columna].visitada) {
            abrir_pared_laberinto(lab, actual, vecino);
            generar_dfs_laberinto(lab, vecino.fila, vecino.columna);
        }
    }
}

void alterar_paredes_laberinto(Laberinto* lab, int porcentaje) {
    srand(time(NULL));
    generar_dfs_laberinto(lab, 0, 0);

    int paredes_extra = (lab->filas * lab->columnas * porcentaje) / 100;
    int abiertas = 0;
    int intentos = 0;
    int max_intentos = paredes_extra * 20; //evita bucle infinito si quedan pocas paredes cerradas

    while (abiertas < paredes_extra && intentos < max_intentos) {
        intentos++;
        int fila = rand() % lab->filas;
        int columna = rand() % lab->columnas;
        Posicion actual = {fila, columna};
        Direccion dir = (Direccion)(rand() % 4);
        Posicion vecino = laberinto_vecino(actual, dir);

        //Solo cuenta si la pared estaba cerrada: cada apertura crea un ciclo nuevo
        if (laberinto_valido(lab, vecino) && !moverse_laberinto(lab, actual, dir)) {
            abrir_pared_laberinto(lab, actual, vecino);
            abiertas++;
        }
    }
}

int moverse_laberinto(Laberinto* lab, Posicion pos, Direccion dir) {
    if (!laberinto_valido(lab, pos)) {
        return 0; // Posición inválida
    }

    Posicion vecino = laberinto_vecino(pos, dir);
    if (!laberinto_valido(lab, vecino)) {
        return 0; // Vecino fuera de los límites
    }

    switch (dir) {
        case ARRIBA:
            return !lab->grilla[pos.fila][pos.columna].pared_arriba;
        case ABAJO:
            return !lab->grilla[pos.fila][pos.columna].pared_abajo;
        case IZQUIERDA:
            return !lab->grilla[pos.fila][pos.columna].pared_izquierda;
        case DERECHA:
            return !lab->grilla[pos.fila][pos.columna].pared_derecha;
    }
    return 0; // Dirección inválida
}

void destruir_laberinto(Laberinto* lab) {
    if (lab == NULL) {
        return;
    }

    for (int i = 0; i < lab->filas; i++) {
        free(lab->grilla[i]);
    }
    free(lab->grilla);
    free(lab);
}