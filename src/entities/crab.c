#include "../raylib.h"
#include "crab.h"

Crab createCrab(Vector2 position, int frameSpeed) {
    Crab crab;
    crab.position = position;
    crab.hitbox = (Rectangle){position.x, position.y, CRAB_WIDTH, CRAB_HEIGHT};
    crab.currentFrame = 0;
    crab.frameCounter = 0;
    crab.frameSpeed = frameSpeed;
    return crab;
}

void updateCrab(Crab* crab) {
    crab->frameCounter++;
    if (crab->frameCounter >= crab->frameSpeed) {
        crab->currentFrame++;
        if (crab->currentFrame >= CRAB_NUM_FRAMES) {
            crab->currentFrame = 0;
        }
        crab->frameCounter = 0;
    }
}

void drawCrab(Crab crab, Texture2D crabTexture) {
    Rectangle sourceRec = {crab.currentFrame * CRAB_WIDTH, 0, CRAB_WIDTH, CRAB_HEIGHT};
    DrawTextureRec(crabTexture, sourceRec, crab.position, WHITE);
}