#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laberinto.h"

void dibujar_ui(Laberinto *lab, Posicion teseo, Posicion minotauro, Posicion rehenes[], int rehen_rescatado[]);

int main(void) {
    srand(time(NULL)); //Semilla aleatoria

    int filas = 7, columnas = 7;

    Laberinto* lab = crear_laberinto(filas, columnas);
    if (lab == NULL) {
        printf("ERROR: No se pudo crear el laberinto\n");
        return 1;
    }

    Posicion teseo = {0, 0};
    Posicion minotauro = {filas / 2, columnas / 2};
    Posicion rehenes[3] = {{1, 1}, {filas - 2, 1}, {1, columnas - 2}};
    int rehen_rescatado[3] = {0, 0, 0};

    generar_laberinto(lab, 10);

    printf("LABERINTO GENERADO:\n\n");
    dibujar_ui(lab, teseo, minotauro, rehenes, rehen_rescatado);

    destruir_laberinto(lab);
    return 0;
}
