#include "obstacle.h"
#include <raylib.h>

Obstacle createObstacle(int x, int y, int width, int height) {
    Obstacle obstacle;
    obstacle.x = x;
    obstacle.y = y;
    obstacle.height = height;
    obstacle.width = width;

    return obstacle;
}

void updateObstacle(Obstacle *obstacle) {
    // Atualize a posição, velocidade...
}

void drawObstacle(Obstacle obstacle) {
    // Desenhe o obstáculo usando as funções da raylib
}