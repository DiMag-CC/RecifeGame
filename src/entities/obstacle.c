#include "obstacle.h"
#include <raylib.h>

Obstacle createObstacle(int x, int y, int width, int height, int type, Color color) {
    Obstacle obstacle;
    obstacle.x = x;
    obstacle.y = y;
    obstacle.height = height;
    obstacle.width = width;
    obstacle.type = type;
    obstacle.color = color;

    return obstacle;
}

void updateObstacle(Obstacle *obstacle, float scrollSpeed, float deltaTime) {
    
    obstacle->position.x -= scrollSpeed * deltaTime;
}

void drawObstacle(Obstacle obstacle) {
    
    DrawRectangleV(obstacle.position, (Vector2){obstacle.width, obstacle.height}, obstacle.color);
}