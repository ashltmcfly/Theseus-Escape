#include <stdlib.h>
#include "teseo.h"
#include "laberinto.h"
#include "cola.h"

// estado inicial de Teseo al iniciar la partidaa
void inicializar_teseo(Teseo_Estado *t, Posicion inicio, 
    Posicion rehenes[NUMERO_REHENES]) {
        t->pos = inicio;
        t->rehenes_restantes = NUMERO_REHENES;

        for (int i = 0; i < NUMERO_REHENES; i++) {
            t->rehenes[i] = rehenes[i];
            t->rehenes_rescatados[i] = 0;
    }
}
// función para controlar el movimiento manual de Teseo (w, s, a, d)
int mover_teseo(Teseo_Estado *t, Laberinto *lab, char tecla) {
    Direccion dir;
    int tecla_valida = 0;

    switch (tecla) {
        case 'w': case 'W':
            dir = ARRIBA;
            tecla_valida = 1;
            break;
        case 's': case 'S':
            dir = ABAJO;
            tecla_valida = 1;
            break;
        case 'a': case 'A':
            dir = IZQUIERDA;
            tecla_valida = 1;
            break;
        case 'd': case 'D':
            dir = DERECHA;
            tecla_valida = 1;
            break;
        default:
            return 0; // si es diferente de W, S, A o D
    }

    if (tecla_valida) {
        if (moverse_laberinto(lab, t->pos, dir)) {
            t->pos = laberinto_vecino(t->pos, dir);
            return 1;
        }
    }
    return 0; // si teseo se topa con una pared ofc
}


// función que controla el rescate de c/rehén
int rescatar_rehen(Teseo_Estado *t) {
    for (int i = 0; i < NUMERO_REHENES; i++) {
        if (t->pos.fila == t->rehenes[i].fila && t->pos.columna == t->rehenes[i].columna) { // si la posición de teseo (x, y) == la posición del rehém
            if (t->rehenes_rescatados[i] == 0) { // si el rehén no ha sido rescatado aún
                t->rehenes_rescatados[i] = 1;
                t->rehenes_restantes--;
                return 1;
            }
        }
    }
    return 0; // siempre que la posición de Teseo no sea la misma de cualquier rehén
}

// función para asegurar que todos los rehenes fueron rescatados (o no)
int final_partida(Teseo_Estado *t) { 
    if (t->rehenes_restantes == 0) {
        return 1;
    }
    return 0;
}

// si es que da tiempo
//void pista_bfs(Teseo_Estado *t, Laberinto *lab) {
//} 