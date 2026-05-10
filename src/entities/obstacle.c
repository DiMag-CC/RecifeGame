#include "obstacle.h"
#include <raylib.h>

Obstacle createObstacle(Vector2 position, ObstacleType type) {
    Obstacle obstacle;
    obstacle.position = position;
    obstacle.type = type;
    
    switch (type) {
        case OBSTACLE_CRAB:
            obstacle.data.crab = createCrab(position, CRAB_FRAME_SPEED);
            break;
        case OBSTACLE_SHARK:
            obstacle.data.shark = createShark(position, (Vector2){0, 0});
            break;
        default:
            // Inicialize outros tipos de obstáculos conforme necessário
            break;
    }
    
    return obstacle;
}

void updateObstacle(Obstacle* obstacle, Vector2 playerPosition, float deltaTime) {
    switch (obstacle->type) {
        case OBSTACLE_CRAB:
            updateCrab(&obstacle->data.crab);
            break;
        case OBSTACLE_SHARK:
            updateShark(&obstacle->data.shark, playerPosition, deltaTime);
            break;
        default:
            // Atualize outros tipos de obstáculos conforme necessário
            break;
    }
}

void drawObstacle(Obstacle obstacle, Texture2D crabTexture, Texture2D sharkTexture) {
    switch (obstacle.type) {
        case OBSTACLE_CRAB:
            drawCrab(obstacle.data.crab, crabTexture);
            break;
        case OBSTACLE_SHARK:
            drawShark(obstacle.data.shark, sharkTexture);
            break;
        default:
            // Desenhe outros tipos de obstáculos conforme necessário
            break;
    }
}