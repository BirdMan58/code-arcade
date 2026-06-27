#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "logic.h"

#define upperBound(val, max) (val+1 > max-1) ? max-1 : val+1
#define lowerBound(val, min) (val-1 < min) ? min : val-1

int board[16][16] = {0};
State boardState[16][16] = {0};
int gameOver = 0;
int gameStart = 0;
int hiddenCells = 1;
int flagCount;

void replay() {
   for (int i = 0; i < gameConfig.row; i++) {
        for (int j = 0; j < gameConfig.row; j++) {
            boardState[i][j] = HIDDEN;
            board[i][j] = 0;
        }
    } 
    hiddenCells = gameConfig.row * gameConfig.row;
    flagCount = gameConfig.totalBombs;
    gameOver = 0;
}

void intilizeBoard(int inputR, int inputC) {
    int r,c;
    int lowRow, lowCol;
    int highRow, highCol;

    hiddenCells = gameConfig.row * gameConfig.row;
    flagCount = gameConfig.totalBombs;

    for(int i = 0; i < gameConfig.totalBombs; i++) {
        do {
            r = rand() % gameConfig.row;
            c = rand() % gameConfig.row;
        } while(board[r][c] == -1 || (inputR == r && inputC == c));

        board[r][c] = -1;
    }

    for (int i = 0; i < gameConfig.row; i++) {
        for (int j = 0; j < gameConfig.row; j++) {
            if(board[i][j] == -1) {
                lowRow = lowerBound(i, 0);
                lowCol = lowerBound(j, 0); 

                highRow = upperBound(i, gameConfig.row);
                highCol = upperBound(j, gameConfig.row);

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

    lowRow = lowerBound(row, 0);
    lowCol = lowerBound(col, 0); 

    highRow = upperBound(row, gameConfig.row);
    highCol = upperBound(col, gameConfig.row);

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
    int lowRow = lowerBound(row, 0);
    int lowCol = lowerBound(col, 0); 

    int highRow = upperBound(row, gameConfig.row);
    int highCol = upperBound(col, gameConfig.row);

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
    }

    if(row < 0 || row >= gameConfig.row || col < 0 || col >= gameConfig.row) {
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