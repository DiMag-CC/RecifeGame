#ifndef PIGEON_H
#define PIGEON_H

#include <raylib.h>

#define PIGEON_WIDTH 40
#define PIGEON_HEIGHT 30
#define PIGEON_SPEED 150.0f
#define PIGEON_POOP_INTERVAL 1.5f 

typedef struct Pigeon {
    Vector2 position;
    float speed;
    float poopTimer;
    int isActive;
} Pigeon;

Pigeon createPigeon(Vector2 position);
int updatePigeon(Pigeon* pigeon, float deltaTime);
void drawPigeon(Pigeon pigeon);

#endif