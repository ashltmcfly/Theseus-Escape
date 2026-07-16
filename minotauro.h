#ifndef MINOTAURO_H
#define MINOTAURO_H

#include "laberinto.h"
#include "cola.h"

Posicion mino_next_step(Laberinto* lab, Posicion posMi, Posicion posTe);
// funcion del minotauro para q busque el siguiente paso a seguir
// "posMi" representa la posicion actual del minotauro, igual con "posTe"
#endif