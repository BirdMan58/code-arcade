#ifndef VIEW_H
#define VIEW_H

#include <raylib.h>

void loadRes();
void unloadRes();
Vector2 translateToBoardPoints(Vector2 mousePos);
void drawBoard();
void drawBoard();
void drawHover(Vector2 hoverPoints);
void drawGameOverMessage(const char* message);
void toggleTheme();
void updateBlockSize();
#endif