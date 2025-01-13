CC = gcc
CFLAGS = -Wall -I/usr/include/SDL2 -I../include -D_REENTRANT
LDFLAGS = -lSDL2 -lm

SRC = src/main.c src/mylib.c
OBJ = build/main.o build/mylib.o
OUT = build/main

all: $(OUT)

$(OUT): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

build/%.o: src/%.c
	mkdir -p build
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
