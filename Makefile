CC = gcc
CFLAGS = -W -Wall -ansi -std=c99
LDFLAGS = -lm `sdl2-config --cflags --libs`
EXEC = main
SRC = Affichage.c Main.c Initialisation.c PathfindingA*.c
OBJ = $(SRC:.c=.o)

all: $(EXEC)
main: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)
clean:
	rm -rf *.o *~
mrproper: clean
	rm -rf $(EXEC)
