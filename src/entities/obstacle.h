#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <raylib.h>
#include "crab.h"
#include "shark.h"

typedef enum {
    OBSTACLE_CRAB = 0,
    OBSTACLE_SHARK = 1
} ObstacleType;

typedef struct {
    Vector2 position;
    ObstacleType type;
    union {
        Crab crab;
        Shark shark;
    } data;
} Obstacle;

Obstacle createObstacle(Vector2 position, ObstacleType type);
void updateObstacle(Obstacle* obstacle, Vector2 playerPosition, float deltaTime);
void drawObstacle(Obstacle obstacle, Texture2D crabTexture, Texture2D sharkTexture);

#endif
