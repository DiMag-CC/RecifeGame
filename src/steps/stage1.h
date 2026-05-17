#ifndef STAGE1_H
#define STAGE1_H

#include <raylib.h>
#include "../structure/obstacleQueue.h"
#include "../entities/player.h"
#include "../entities/pigeon.h"
#include "../entities/raindrop.h"
#include "../entities/umbrella.h"

#define MAX_PIGEONS 10
#define MAX_RAINDROPS 100

typedef struct Stage1 {
    float scrollSpeed;  
    Texture2D background;  
    Texture2D buildings[8];  
    float roadPosition;  
    ObstacleQueue obstacleQueue;
    float obstacleSpawnTimer;
    float distanceTraveled;
    
    float spawnInterval;
    int stage1Complete;
    float difficultyMultiplier;
    
    int pigeonCount;
    Pigeon pigeons[MAX_PIGEONS];
    
    int raindropCount;
    float rainSpawnTimer;
    float rainSpawnInterval;
    Raindrop raindrops[MAX_RAINDROPS];
    
    int umbrellasSpawned;
    Umbrella umbrellas[2];
} Stage1;

void initStage1(Stage1* stage);  
void updateStage1(Stage1* stage, Player *player, float deltaTime);  
void drawStage1(Stage1 *stage, Player *player);  
void unloadStage1(Stage1* stage);  

#endif
