#ifndef COLA_H
#define COLA_H

//Estructura posicion en el laberinto
typedef struct {
    int fila;
    int columna;
} Posicion;

//Estructura nodo de la cola
typedef struct ColaNodo {
    Posicion dato;
    struct ColaNodo* siguiente;
} ColaNodo;

//Estructura cola FIFO
typedef struct {
    ColaNodo* frente;
    ColaNodo* final;
    int tamano;
} Cola;

//Funciones para manejar la cola

//Crear cola vacia reservando memoria con malloc
Cola* cola_crear(void);

//Agregar posicion al final de la cola, creando un nuevo ColaNodo con malloc
int cola_encolar(Cola* cola, Posicion pos);

//Eliminar posicion del frente de la cola y devolverla
Posicion cola_desencolar(Cola* cola);

//Verificar si la cola está vacía
int cola_vacia(Cola* cola);

//Destruir la cola y liberar la memoria
void cola_destruir(Cola* cola);

#endif
