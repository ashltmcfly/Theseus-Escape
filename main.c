#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laberinto.h"
#include "minotauro.h"
#include "teseo.h"
#include "minotauro.h"

void dibujar_ui(Laberinto *lab, Posicion teseo, Posicion minotauro, Posicion rehenes[], int rehen_rescatado[]);

int main(void) {
    srand(time(NULL)); 

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

    printf("LABERINTO INICIAL:\n\n");
    dibujar_ui(lab, teseo, minotauro, rehenes, rehen_rescatado);
    getchar();
    generar_laberinto(lab, 20);

    printf("LABERINTO GENERADO:\n\n");
    dibujar_ui(lab, teseo, minotauro, rehenes, rehen_rescatado);
    getchar();
    
    for (int turno = 0; turno < 100; turno++) {
        printf("TURNO %d:\n\n", turno + 1);

        Posicion siguiente_minotauro = mino_next_step(lab, minotauro, teseo);
        dibujar_ui(lab, teseo, siguiente_minotauro, rehenes, rehen_rescatado);
        getchar();
        minotauro = siguiente_minotauro;
        // Aquí puedes agregar la lógica para mover a Teseo y al Minotauro
        // Por ejemplo, podrías pedir al usuario que ingrese un movimiento para Teseo
        // y luego calcular el siguiente movimiento del Minotauro usando mino_next_step.

        if (minotauro.fila == teseo.fila && minotauro.columna == teseo.columna) {
            printf("El Minotauro ha atrapado a Teseo. Fin del juego.\n");
            break;
        }
    }

    destruir_laberinto(lab);
    return 0;
}
