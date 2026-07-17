#ifndef TESEO_H
#define TESEO_H

#include "cola.h"
#include "laberinto.h"
#define NUMERO_REHENES 3

typedef struct {
    Posicion pos;
    Posicion rehenes[NUMERO_REHENES];
    int rehenes_rescatados[NUMERO_REHENES]; // array binario (0=sin rescatar, 1=rescatado)
    int rehenes_restantes; // contador -
} Teseo_Estado;

void inicializar_teseo(Teseo_Estado *t, Posicion teseo, Posicion rehenes[NUMERO_REHENES]);
int mover_teseo(Teseo_Estado *t, Laberinto *lab, char tecla);
int rescatar_rehen(Teseo_Estado *t);
int final_partida(Teseo_Estado *t);
//void pista_bfs(Teseo_Estado *t, Laberinto *lab); //si da tiempo

#endif
