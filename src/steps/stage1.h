#ifndef STAGE1_H
#define STAGE1_H

#include <raylib.h>
#include "../structure/obstacleQueue.h"
#include "../entities/player.h"

typedef struct Stage1 {
    float scrollSpeed;  
    Texture2D background;  
    Texture2D buildings[5];  
    float roadPosition;  
    ObstacleQueue obstacleQueue;
    float obstacleSpawnTimer;
    float distanceTraveled;
} Stage1;

void initStage1(Stage1* stage);  
void updateStage1(Stage1* stage, Player *player, float deltaTime);  
void drawStage1(Stage1 *stage);  
void unloadStage1(Stage1* stage);  

#endif
