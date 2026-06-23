#ifndef LOGIC_H
#define LOGIC_H

#include "config.h"

typedef enum {
    HIDDEN,
    VISIBLE,
    FLAGED,
    QUESTIONED,
    BOMBED,
    MISFLAGED
} State;

extern int board[HEIGHT][WIDTH];
extern State boardState[HEIGHT][WIDTH];
extern int gameOver;
extern int gameStart;

void intilizeBoard(int inputR, int inputC);
int handleInput(int row, int col);
void flagIt(int row, int col);
int gameWon();
void replay();

#endif