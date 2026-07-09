#include <stdio.h>
#include <stdlib.h>

#include "cola.h"
#include "laberinto.h"

void ui_limpiar(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void dibujar_ui(Laberinto *lab, Posicion teseo, Posicion minotauro, Posicion rehenes[], int rehen_rescatado[]) {
    ui_limpiar();
    for (int i = 0; i < lab->filas; i++) {
        //Línea de paredes superiores (compartida con la fila anterior)
        for (int j = 0; j <= lab->columnas; j++) {
            if (i == 0) {
                if (j == 0) {
                    printf("╔");
                } else if (j == lab->columnas) {
                    printf("╗");
                } else {
                    printf("╦");
                }
            } else {
                if (j == 0) {
                    printf("╠");
                } else if (j == lab->columnas) {
                    printf("╣");
                } else {
                    printf("╬");
                }
            }

            if (j < lab->columnas) {
                if (lab->grilla[i][j].pared_arriba) {
                    printf("════");
                } else {
                    printf("    ");
                }
            }
        }
        printf("\n");

        //Línea de contenido: pared izquierda de cada celda + borde derecho final
        for (int j = 0; j < lab->columnas; j++) {
            if (lab->grilla[i][j].pared_izquierda) {
                printf("║");
            } else {
                printf(" ");
            }

            if (teseo.fila == i && teseo.columna == j) {
                printf(" T  ");
            } else if (minotauro.fila == i && minotauro.columna == j) {
                printf(" M  ");
            } else {
                int es_rehen = 0;
                for (int k = 0; k < 3; k++) {
                    if (rehenes[k].fila == i && rehenes[k].columna == j && !rehen_rescatado[k]) {
                        printf(" R  ");
                        es_rehen = 1;
                        break;
                    }
                }
                if (!es_rehen) printf("    ");
            }
        }
        if (lab->grilla[i][lab->columnas - 1].pared_derecha) {
            printf("║");
        } else {
            printf(" ");
        }
        printf("\n");
    }

    //Borde inferior del laberinto
    for (int j = 0; j <= lab->columnas; j++) {
        if (j == 0) {
            printf("╚");
        } else if (j == lab->columnas) {
            printf("╝");
        } else {
            printf("╩");
        }

        if (j < lab->columnas) {
            if (lab->grilla[lab->filas - 1][j].pared_abajo) {
                printf("════");
            } else {
                printf("    ");
            }
        }
    }
    printf("\n");
}
