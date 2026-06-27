#include "config.h"

int isLevelEasy = 1;

GameConfig gameConfig = {
        .col = 9,
        .row = 9,
        .totalBombs = 10
    };

void changeLevel() {
    if(isLevelEasy) {
        gameConfig = (GameConfig) {16, 16, 40};
        isLevelEasy = 0;
    } else {
        gameConfig = (GameConfig) {9, 9, 10};
        isLevelEasy = 1;
    }
}