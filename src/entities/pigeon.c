#include "pigeon.h"

Pigeon createPigeon(Vector2 position) {
    Pigeon pigeon;
    pigeon.position = position;
    pigeon.speed = PIGEON_SPEED;
    pigeon.poopTimer = 0.0f;
    pigeon.isActive = 1;

    return pigeon;
}

int updatePigeon(Pigeon *pigeon, float deltaTime) {
    if (!pigeon->isActive) return 0;

    pigeon->position.x -= pigeon->speed * deltaTime;

    pigeon->poopTimer += deltaTime;

    int shouldPoop = 0;
    if (pigeon->poopTimer >= PIGEON_POOP_INTERVAL) {
        shouldPoop = 1; // Momento de cagar
        pigeon->poopTimer = 0.0f; 
    }

    if (pigeon->position.x < -PIGEON_WIDTH) {
        pigeon->isActive = 0;
    }
    
    return shouldPoop;
}

void drawPigeon(Pigeon pigeon) {
    if (!pigeon.isActive) return;
    
    DrawRectangle(
        pigeon.position.x,
        pigeon.position.y,
        PIGEON_WIDTH,
        PIGEON_HEIGHT,
        DARKGRAY
    );
    
    DrawCircle(
        pigeon.position.x + PIGEON_WIDTH - 8,
        pigeon.position.y + 8,
        3,
        BLACK
    );
    
    DrawLine(
        pigeon.position.x + 10,
        pigeon.position.y + 10,
        pigeon.position.x + 5,
        pigeon.position.y + 5,
        BLACK
    );
}