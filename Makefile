CC = gcc
CFLAGS = -Wall $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)
SRC = src/main.c
OBJ = build/main.o
EXEC = build/main

# La règle par défaut
all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $(OBJ) $(LDFLAGS)

# Construire les fichiers objets dans build/obj
build/main.o: src/main.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f build/*.o $(EXEC)

install:
	cp $(EXEC) /usr/local/bin
