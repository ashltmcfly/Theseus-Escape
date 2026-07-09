#ifndef LABERINTO_H
#define LABERINTO_H

#include "cola.h"

//Estructura de movimientos
typedef enum {
    ARRIBA,
    ABAJO,
    IZQUIERDA,
    DERECHA
} Direccion;

//Estructura de la celda del laberinto
typedef struct {
    int pared_arriba;
    int pared_abajo;
    int pared_izquierda;
    int pared_derecha;
    int visitada;  //usado SOLO durante la generación DFS
} Celda;

//Estructura del laberinto completo
typedef struct {
    Celda** grilla;  //grilla[fila][columna]
    int filas;
    int columnas;
} Laberinto;

//Funciones para manejar la cola

//Crear laberinto con todas las paredes cerradas y visitada=0
Laberinto* crear_laberinto(int filas, int columnas);

//Generar laberinto con DFS
void alterar_paredes_laberinto(Laberinto* lab, int porcentaje);

//Abrir el pasillo entre dos celdas adyacentes
void abrir_pared_laberinto(Laberinto* lab, Posicion a, Posicion b);

//Cerrar el pasillo entre dos celdas adyacentes (pone pared entre a y b)
void cerrar_pared_laberinto(Laberinto* lab, Posicion a, Posicion b);

//Posicion del vecino en la dirección dada
Posicion laberinto_vecino(Posicion pos, Direccion dir);

//Retorna 1 si la posición está dentro de los límites del laberinto
int laberinto_valido(Laberinto* lab, Posicion pos);

//Moverse por el laberinto
int moverse_laberinto(Laberinto* lab, Posicion pos, Direccion dir);

//Destruir el laberinto y liberar la memoria
void destruir_laberinto(Laberinto* lab);
#endif
