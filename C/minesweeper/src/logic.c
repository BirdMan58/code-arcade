#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "config.h"
#include "logic.h"

int board[HEIGHT][WIDTH] = {0};
State boardState[HEIGHT][WIDTH] = {0};
int gameOver = 0;
int gameStart = 0;
int hiddenCells = HEIGHT * WIDTH;
int flagCount = TOTALBOMBS;

void replay() {
   for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            boardState[i][j] = HIDDEN;
            board[i][j] = 0;
        }
    } 
    hiddenCells = HEIGHT * WIDTH;
    flagCount = TOTALBOMBS;
    gameOver = 0;
}

void intilizeBoard(int inputR, int inputC) {
    int r,c;
    int lowRow, lowCol;
    int highRow, highCol;

    for(int i = 0; i < TOTALBOMBS; i++) {
        do {
            r = rand() % HEIGHT;
            c = rand() % WIDTH;
        } while(board[r][c] == -1 || (inputR == r && inputC == c));

        board[r][c] = -1;
    }

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if(board[i][j] == -1) {
                lowRow = (i-1 < 0) ? 0 : i-1;
                lowCol = (j-1 < 0) ? 0 : j-1; 

                highRow = (i+1 > 8) ? 8 : i+1;
                highCol = (j+1 > 8) ? 8 : j+1;

                for (int k = lowRow; k <= highRow; k++) {
                    for (int l = lowCol; l <= highCol; l++) {
                        if(board[k][l] != -1) {
                            board[k][l]++;
                        }
                    }
                }
            }
        }
    }

    gameStart = 1;
}

static void makeVisible(int row, int col) {
    if(boardState[row][col] != VISIBLE) {
        boardState[row][col] = VISIBLE;
        hiddenCells--;
    }
}

static void blankCase(int row, int col) {
    int lowRow, lowCol;
    int highRow, highCol;

    if(boardState[row][col] == VISIBLE) {
        return;
    }
    makeVisible(row, col);

    lowRow = (row-1 < 0) ? 0 : row-1;
    lowCol = (col-1 < 0) ? 0 : col-1; 

    highRow = (row+1 > 8) ? 8 : row+1;
    highCol = (col+1 > 8) ? 8 : col+1;

    for (int i = lowRow; i <= highRow; i++) {
        for (int j = lowCol; j <= highCol; j++) {      
            if(board[i][j] == 0) {
                blankCase(i, j);
            } else if(board[i][j] != -1) {
                makeVisible(i, j);
            }
        }
    }
}

static int showNeighbour(int row, int col) {
    int lowRow = (row-1 < 0) ? 0 : row-1;
    int lowCol = (col-1 < 0) ? 0 : col-1; 

    int highRow = (row+1 > 8) ? 8 : row+1;
    int highCol = (col+1 > 8) ? 8 : col+1;

    int placedFlags = 0;
    for (int i = lowRow; i <= highRow; i++) {
        for (int j = lowCol; j <= highCol; j++) {      
            if(boardState[i][j] == FLAGED || boardState[i][j] == MISFLAGED) {
                placedFlags++;
            }
        }
    }

    if(placedFlags < board[row][col]) {
        return 0;
    }

    for (int i = lowRow; i <= highRow; i++) {
        for (int j = lowCol; j <= highCol; j++) {
            if(board[i][j] == 0) {
                blankCase(i, j);
            } else if(boardState[i][j] != FLAGED && boardState[i][j] != MISFLAGED && boardState[i][j] != QUESTIONED) {
                if(board[i][j] != -1) {
                    makeVisible(i, j);
                } else {
                    boardState[i][j] = BOMBED;
                    gameOver = 1;
                }
            }
        }
    }
    return 1;
}

int handleInput(int row, int col) {
    if(!gameStart) {
        intilizeBoard(row, col);
        TraceLog(LOG_INFO, "Game has begun!");
    }

    if(row < 0 || row > 8 || col < 0 || col > 8) {
        return 0;
    } 

    if(board[row][col] == 0) {
        blankCase(row, col);
    } else if(board[row][col] == -1) {
        boardState[row][col] = BOMBED;
        gameOver = 1;
    } else if(boardState[row][col] == HIDDEN) {
        makeVisible(row, col);
    } else {
        showNeighbour(row, col);
    }
    // TraceLog(LOG_INFO, "Hidden Cells: %d", hiddenCells);
    return 1;
}

void flagIt(int row, int col) {
    if(boardState[row][col] == HIDDEN && flagCount != 0) {
        boardState[row][col] = (board[row][col] == -1) ? FLAGED : MISFLAGED;
        flagCount--;
        hiddenCells--;
    } else if(boardState[row][col] == FLAGED || boardState[row][col] == MISFLAGED) {
        boardState[row][col] = QUESTIONED;
        flagCount++;
        hiddenCells++;
    } else if(boardState[row][col] == QUESTIONED) {
        boardState[row][col] = HIDDEN;
    }
}

int gameWon() {
    return (hiddenCells == 0);
}