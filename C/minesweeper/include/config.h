#ifndef CONFIG_H
#define CONFIG_H

#include <raylib.h>

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 800

#define SPRITE_ROW 5
#define SPRITE_COL 4

#define ZERO        (Vector2) {0, 0}
#define ONE         (Vector2) {0, 1}
#define TWO         (Vector2) {0, 2}
#define THREE       (Vector2) {0, 3}

#define FOUR        (Vector2) {1, 0}
#define FIVE        (Vector2) {1, 1}
#define SIX         (Vector2) {1, 2}
#define SEVEN       (Vector2) {1, 3}

#define EIGHT       (Vector2) {2, 0}
#define BOMB        (Vector2) {2, 1}
#define RED_BOMB    (Vector2) {2, 2}
#define CROSS_BOMB  (Vector2) {2, 3}

#define QUESTION    (Vector2) {3, 0}
#define FLAG        (Vector2) {3, 1}
#define CELL        (Vector2) {3, 2}

#define QUESTION_HOVER (Vector2) {4, 0}
#define FLAG_HOVER  (Vector2) {4, 1}
#define CELL_HOVER  (Vector2) {4, 2}

typedef struct {
    int row;
    int col;
    int totalBombs;
} GameConfig;

extern GameConfig gameConfig;

void changeLevel();
#endif