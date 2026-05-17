#ifndef STAGE3_H
#define STAGE3_H

#include <raylib.h>
#include "../entities/player.h"

#define MAX_CLOUDS 2
#define MAX_BIRDS 3
#define MAX_BIRD_POOPS 10

typedef enum {
    STAGE3_APPROACH, // Camera horizontal ate encontrar a torre
    STAGE3_CLIMBING, // Jogador escala, scroll vertical
    STAGE3_FINISHED
} Stage3State;

typedef struct {
    Vector2 position;
    float speed;
    float scale;
} Cloud;

typedef struct {
    Vector2 position;
    float speed;
    float poopTimer;
    float poopInterval;
} Bird;

typedef struct {
    Vector2 position;
    bool active;
    float speedY;
} BirdPoop;

typedef struct Stage3 {
    Stage3State state;
    Texture2D towerTexture;
    Texture2D cloudTexture;
    Texture2D birdTexture;
    
    float scrollX;
    float scrollY;
    
    Rectangle towerHitbox;
    Vector2 towerPosition;
    
    Cloud clouds[MAX_CLOUDS];
    Bird birds[MAX_BIRDS];
    BirdPoop poops[MAX_BIRD_POOPS];
    
} Stage3;

void initStage3(Stage3 *stage, Player *player);
void updateStage3(Stage3 *stage, Player *player, float deltaTime);
void drawStage3(Stage3 *stage, Player *player);
void unloadStage3(Stage3 *stage);

#endif
