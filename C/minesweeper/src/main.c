#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <raylib.h>

#include "config.h"
#include "logic.h"
#include "view.h"

int main() {
    srand(time(NULL));
    Image icon = LoadImage("./res/icon.png");

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MineSweeper!");
    SetWindowIcon(icon);
    UnloadImage(icon);

    SetTargetFPS(60);

    loadRes();

    Vector2 mousePos = {0, 0};
    Vector2 boardPoints = {0, 0};

    while(!WindowShouldClose()) {
        mousePos = GetMousePosition();
        boardPoints = translateToBoardPoints(mousePos);

        if(IsKeyPressed(KEY_N)) {
            gameStart = 0;
            replay();
        }
        if(IsKeyPressed(KEY_Q)) {
            break;
        }
        if(IsKeyPressed(KEY_T)) {
            toggleTheme();
        }
        if(IsKeyPressed(KEY_L)) {
            changeLevel();
            updateBlockSize();
            gameStart = 0;
            replay();
        }
        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            mousePos =  GetMousePosition();
            boardPoints = translateToBoardPoints(mousePos);

            handleInput(boardPoints.y, boardPoints.x);
        } 
        if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            mousePos =  GetMousePosition();
            boardPoints = translateToBoardPoints(mousePos);

            flagIt(boardPoints.y, boardPoints.x);
        }
        
        BeginDrawing();
            ClearBackground(CLITERAL (Color) {53, 60, 74, 255});
            drawBoard();
            drawHover(boardPoints);
            if(gameWon()) {
                drawGameOverMessage("Yay! you Won!");
            } else if(gameOver) {
                drawGameOverMessage("Oops! you Lose!");
            }
        EndDrawing();
    }

    unloadRes();
    CloseWindow();

    return 0;
}