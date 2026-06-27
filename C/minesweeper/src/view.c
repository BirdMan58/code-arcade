#include <stdio.h>
#include <stdlib.h>

#include <raylib.h>

#include "config.h"
#include "logic.h"

int padding;
float blockSize;

Rectangle srcRec;
Rectangle dstRec;
float frameHeight;
float frameWidth;

Texture2D spriteSheet;
Texture2D lightTheme;
Texture2D darkTheme;
int isThemeLight = 1;
Font font;

Vector2 position = {0, 0};
Vector2 spriteLoc;
Vector2 offset;

void updateBlockSize() {
    int bigside = ((gameConfig.row < gameConfig.col) ? gameConfig.col : gameConfig.row);
    padding = ((gameConfig.row > 10 || gameConfig.col > 10) ? 2 : 5);
    blockSize = ((SCREEN_HEIGHT < SCREEN_WIDTH) ? (SCREEN_HEIGHT / bigside) - padding : (SCREEN_WIDTH / bigside) - padding);

    dstRec = (Rectangle) {0, 0, blockSize, blockSize};
    offset = (Vector2) {
        .x = (SCREEN_WIDTH - ((blockSize + padding) * gameConfig.col) - padding) / 2,
        .y = (SCREEN_HEIGHT - ((blockSize + padding) * gameConfig.row) - padding) / 2
    };
}

void loadRes() {
    updateBlockSize();

    lightTheme = LoadTexture("./res/spriteSheetLight.png");
    darkTheme = LoadTexture("./res/spriteSheetDark.png");
    spriteSheet = lightTheme;

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
    float size = blockSize + padding;
    
    return (Vector2) {
        (mousePos.x - offset.x) / size, 
        (mousePos.y - offset.y) / size
    };
}

void drawBoard() {
    for (int i = 0; i < gameConfig.row; i++) {
        for (int j = 0; j < gameConfig.col; j++) {
            dstRec.y = offset.y + i*blockSize + padding * (i+1);
            dstRec.x = offset.x + j*blockSize + padding * (j+1);

            switch(boardState[i][j]) {
                case HIDDEN:
                    if(gameOver) {
                        spriteLoc = (board[i][j] == -1) ? BOMB : CELL;
                    } else {
                        spriteLoc = CELL; 
                    }
                    break;
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
                    default: TraceLog(LOG_INFO, "board unnknown char %d", board[i][j]);
                }
                break;
                case FLAGED: spriteLoc = FLAG; break;
                case QUESTIONED: spriteLoc = QUESTION; break;
                case BOMBED: spriteLoc = RED_BOMB; break;
                case MISFLAGED: 
                    spriteLoc = (gameOver) ? CROSS_BOMB : FLAG; 
                    break;
                default: TraceLog(LOG_INFO, "boardstate unnknown char %d", board[i][j]);
            }

            srcRec.x = frameHeight * spriteLoc.y;
            srcRec.y = frameWidth * spriteLoc.x;
            DrawTexturePro(spriteSheet, srcRec, dstRec,  (Vector2) {0, 0}, 0, WHITE);
        }
    }
    
}

void drawHover(Vector2 hoverPoints) {
    if(hoverPoints.y < 0 || hoverPoints.y > gameConfig.row || hoverPoints.x < 0 || hoverPoints.x > gameConfig.col) {
        return;
    }

    int x = hoverPoints.x;
    int y = hoverPoints.y;

    dstRec.x = offset.x + x*blockSize + padding * (x+1);
    dstRec.y = offset.y + y*blockSize + padding * (y+1);

    switch(boardState[y][x]) {
        case HIDDEN: spriteLoc = CELL_HOVER; break;
        case FLAGED: case MISFLAGED: spriteLoc = FLAG_HOVER; break;
        case QUESTIONED: spriteLoc = QUESTION_HOVER; break; 
        default: return;       
    }

    srcRec.x = frameHeight * spriteLoc.y;
    srcRec.y = frameWidth * spriteLoc.x;

    if(!gameOver) {
        DrawTexturePro(spriteSheet, srcRec, dstRec,  (Vector2) {0, 0}, 0, WHITE);
    }
}

void drawGameOverMessage(const char* message) {
    int messageHeight = 400;
    int stPoint = (SCREEN_HEIGHT/2) - messageHeight/2;
    char* thanks = "Thanks for playing\nCreated by BirdMan\n\nPress 'N' for new game";
    DrawRectangle(0, stPoint, SCREEN_WIDTH, messageHeight, (Color) {0, 0, 0, 180});
    DrawTextEx(font, message, (Vector2) {100, stPoint+150}, 75, 6,  WHITE);
    DrawTextEx(font, thanks, (Vector2) {100, stPoint+250}, 25, 2,  WHITE);
}

void toggleTheme() {
    spriteSheet = (isThemeLight) ? darkTheme : lightTheme;
    isThemeLight = (isThemeLight + 1) % 2;
}
