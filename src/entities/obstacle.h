#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <raylib.h>
#include "crab.h"
#include "shark.h"
#include "pigeon.h"

typedef enum {
    OBSTACLE_CRAB = 0,         
    OBSTACLE_POTHOLE = 1,       
    OBSTACLE_PIGEON_POOP = 2,   
    OBSTACLE_BUS = 3,           
    OBSTACLE_PIGEON = 4,       
    OBSTACLE_SHARK = 5         
} ObstacleType;

typedef struct {
    Vector2 position;
    ObstacleType type;
    int active;
    
    union {
        Crab crab;
        Pothole pothole;
        PigeonPoop pigeonPoop;
        Bus bus;
        Pigeon pigeon;        
        Shark shark;
    } data;
} Obstacle;

Obstacle createObstacle(Vector2 position, ObstacleType type);
void updateObstacle(Obstacle* obstacle, Vector2 playerPosition, float deltaTime);
void drawObstacle(Obstacle obstacle, Texture2D crabTexture, Texture2D sharkTexture);

#endif
