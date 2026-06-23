CC = gcc
CFLAGS = -Iinclude $(shell pkg-config --cflags raylib)
LIBS = $(shell pkg-config --libs raylib)

TARGET = ./bin/game
STARGET = ./bin/staticGame
SRC = ./src/main.c ./src/logic.c ./src/view.c

build:
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)
run:
	./bin/game