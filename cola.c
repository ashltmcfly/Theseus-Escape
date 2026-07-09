#include <stdlib.h>
#include "cola.h"

Cola* cola_crear(void) {
    Cola* nueva_cola = malloc(sizeof(Cola));
    if (nueva_cola == NULL) {
        return NULL;
    }
    nueva_cola->frente = NULL;
    nueva_cola->final = NULL;
    nueva_cola->tamano = 0;
    return nueva_cola;
}

void cola_encolar(Cola* cola, Posicion pos) {
    ColaNodo* nuevo_nodo = malloc(sizeof(ColaNodo));
    if (nuevo_nodo == NULL) {
        return;
    }

    nuevo_nodo->dato = pos;
    nuevo_nodo->siguiente = NULL;

    if (cola->frente == NULL) {
        cola->frente = nuevo_nodo;
        cola->final = nuevo_nodo;
    } else {
        cola->final->siguiente = nuevo_nodo;
        cola->final = nuevo_nodo;
    }
    cola->tamano++;
}

Posicion cola_desencolar(Cola* cola) {
    if (cola->frente == NULL) {
        Posicion vacia = {-1, -1}; //Valor de retorno para cola vacía
        return vacia;
    }

    ColaNodo* nodo_temporal = cola->frente;
    Posicion dato_temporal = nodo_temporal->dato;

    cola->frente = nodo_temporal->siguiente;
    if (cola->frente == NULL) {
        cola->final = NULL;
    }

    free(nodo_temporal);
    cola->tamano--;
    return dato_temporal;
}

int cola_vacia(Cola* cola) {
    if (cola->frente == NULL) {
        return 1; // La cola está vacía
    }
    return 0; // La cola no está vacía
}

void cola_destruir(Cola* cola) {
    while (!cola_vacia(cola)) {
        cola_desencolar(cola); // Esto libera cada nodo
    }
    free(cola); // Liberar la estructura Cola
}