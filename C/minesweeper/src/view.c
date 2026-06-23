#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#include "config.h"
#include "logic.h"

Rectangle srcRec;
Rectangle dstRec = {0, 0, BLOCK_SIZE, BLOCK_SIZE};
float frameHeight;
float frameWidth;
Texture2D spriteSheet;
Vector2 position = {0, 0};
Vector2 spriteLoc;
Font font;

void loadRes() {
    spriteSheet = LoadTexture("./res/spriteSheet.png");
    font = GetFontDefault();

    frameHeight = spriteSheet.height / SPRITE_ROW;
    frameWidth = spriteSheet.width / SPRITE_COL;

    srcRec = (Rectangle){frameHeight, frameWidth, frameWidth, frameHeight};
}

void unloadRes(){
    UnloadTexture(spriteSheet);
    UnloadFont(font);
}

Vector2 translateToBoardPoints(Vector2 mousePos) {
    int blockSize = BLOCK_SIZE + PADDING;
    
    return (Vector2) {
        mousePos.x / blockSize, 
        mousePos.y / blockSize
    };
}

void drawBoard() {
    // int blockSize = (height > width) ? (height / HEIGHT) - PADDING : (width / HEIGHT) - PADDING;
    int blockSize = BLOCK_SIZE;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            // DrawRectangle(i*blockSize + 5*(i+1), j*blockSize + 5*(j+1), blockSize, blockSize, CLITERAL (Color){227, 241, 255, 255}); 
            dstRec.x = i*blockSize + 5*(i+1);
            dstRec.y = j*blockSize + 5*(j+1);

            switch(boardState[i][j]) {
                case HIDDEN: spriteLoc = CELL; break;
                case VISIBLE: 
                    switch(board[i][j]) {
                    case -1: spriteLoc = BOMB; break;
                    case  0: spriteLoc = ZERO; break;
                    case  1: spriteLoc = ONE; break;
                    case  2: spriteLoc = TWO; break;
                    case  3: spriteLoc = THREE; break;
                    case  4: spriteLoc = FOUR; break;
                    case  5: spriteLoc = FIVE; break;
                    case  6: spriteLoc = SIX; break;
                    case  7: spriteLoc = SEVEN; break;
                    case  8: spriteLoc = EIGHT; break;
                }
                break;
                case FLAGED: spriteLoc = FLAG; break;
                case QUESTIONED: spriteLoc = QUESTION; break;
                case BOMBED: spriteLoc = RED_BOMB; break;
                case MISFLAGED: 
                    spriteLoc = (gameOver) ? CROSS_BOMB : FLAG; 
                    break;
            }

            srcRec.x = frameHeight * spriteLoc.y;
            srcRec.y = frameWidth * spriteLoc.x;
            DrawTexturePro(spriteSheet, srcRec, dstRec,  (Vector2) {0, 0}, 0, WHITE);
        }
    }
    
}

void drawHover(Vector2 hoverPoints) {
    if(hoverPoints.x < 0 || hoverPoints.x > 9 || hoverPoints.y < 0 || hoverPoints.y > 9) {
        return;
    }
    int blockSize = BLOCK_SIZE;
    int x = hoverPoints.x;
    int y = hoverPoints.y;

    dstRec.x = x*blockSize + 5*(x+1);
    dstRec.y = y*blockSize + 5*(y+1);

    switch(boardState[x][y]) {
        case HIDDEN: spriteLoc = CELL_HOVER; break;
        case FLAGED: case MISFLAGED: spriteLoc = FLAG_HOVER; break;
        case QUESTIONED: spriteLoc = QUESTION_HOVER; break; 
        default: return;       
    }

    srcRec.x = frameHeight * spriteLoc.y;
    srcRec.y = frameWidth * spriteLoc.x;

    DrawTexturePro(spriteSheet, srcRec, dstRec,  (Vector2) {0, 0}, 0, WHITE);
}

void drawGameOverMessage(const char* message) {
    int messageHeight = 400;
    int stPoint = (SCREEN_HEIGHT/2) - messageHeight/2;
    char* thanks = "Thanks for playing\nCreated by BirdMan\n\nPress 'N' for new game";
    DrawRectangle(0, stPoint, SCREEN_WIDTH, messageHeight, (Color) {0, 0, 0, 180});
    DrawTextEx(font, message, (Vector2) {100, stPoint+150}, 75, 6,  WHITE);
    DrawTextEx(font, thanks, (Vector2) {100, stPoint+250}, 25, 2,  WHITE);
}
