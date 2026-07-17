#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "laberinto.h"
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

    Teseo_Estado teseo;
    Posicion teseo_pos = {0, 0};
    Posicion minotauro = {filas / 2, columnas / 2};
    Posicion rehenes[3] = {{1, 1}, {filas - 2, 1}, {1, columnas - 2}};
    //int rehen_rescatado[3] = {0, 0, 0};
    inicializar_teseo(&teseo, teseo_pos, rehenes);

    generar_laberinto(lab, 20);

    printf("LABERINTO GENERADO:\n\n");
    dibujar_ui(lab, teseo.pos, minotauro, rehenes, teseo.rehenes_rescatados);
    getchar();
    
    for (int turno = 0; turno < 100; turno++) {
        printf("========== TURNO %d ==========\n\n", turno + 1);

        // --- TURNO DE TESEO ---
        printf("Controles de Teseo: W(arriba) S(abajo) A(izq) D(der)\n");
        printf("Ingrese movimiento: ");
        
        char tecla;
        scanf("%c", &tecla);
        
        if (mover_teseo(&teseo, lab, tecla)) {
            printf("Teseo se movió.\n");
        } else {
            printf("Movimiento inválido (pared o tecla incorrecta).\n");
        }
        
        // Intentar rescatar rehén si está en la misma posición
        if (rescatar_rehen(&teseo)) {
            printf("¡Teseo rescató a un rehén! Rehenes restantes: %d\n", 
                   teseo.rehenes_restantes);
        }
        
        // Verificar victoria
        if (final_partida(&teseo)) {
            printf("\n¡¡¡TESEO GANÓ!!! Todos los rehenes fueron rescatados.\n");
            break;
        }

        printf("\nPulsa Enter para que el Minotauro se mueva...\n");
        
        // --- TURNO DEL MINOTAURO ---
        printf("El Minotauro se mueve...\n");
        Posicion siguiente_minotauro = mino_next_step(lab, minotauro, teseo.pos);
        minotauro = siguiente_minotauro;
        getchar(); // consumir enter anterior
        getchar();
        // Mostrar estado del juego
        printf("\nPosición de Teseo: (%d, %d)\n", teseo.pos.fila, teseo.pos.columna);
        printf("Posición del Minotauro: (%d, %d)\n\n", minotauro.fila, minotauro.columna);
        
        dibujar_ui(lab, teseo.pos, minotauro, rehenes, teseo.rehenes_rescatados);
        
        // Verificar derrota (Minotauro atrapa a Teseo)
        if (minotauro.fila == teseo.pos.fila && 
            minotauro.columna == teseo.pos.columna) {
            printf("\n¡¡¡EL MINOTAURO ATRAPÓ A TESEO!!! Fin del juego.\n");
            break;
        }
    }

    destruir_laberinto(lab);
    return 0;
}
