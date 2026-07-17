CC = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ = main.o laberinto.o cola.o ui.o minotauro.o teseo.o

theseus: $(OBJ)
	$(CC) $(CFLAGS) -o theseus $(OBJ)

main.o: main.c laberinto.h minotauro.h teseo.h
	$(CC) $(CFLAGS) -c main.c

laberinto.o: laberinto.c laberinto.h cola.h
	$(CC) $(CFLAGS) -c laberinto.c

cola.o: cola.c cola.h
	$(CC) $(CFLAGS) -c cola.c

ui.o: ui.c laberinto.h cola.h
	$(CC) $(CFLAGS) -c ui.c

minotauro.o: minotauro.c minotauro.h laberinto.h cola.h
	$(CC) $(CFLAGS) -c minotauro.c

teseo.o: teseo.c teseo.h laberinto.h cola.h
	$(CC) $(CFLAGS) -c teseo.c

clean:
	rm -f *.o theseus theseus.exe

.PHONY: clean