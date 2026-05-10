#ifndef CRAB_H
#define CRAB_H

#include <raylib.h>

#define CRAB_WIDTH 64
#define CRAB_HEIGHT 64
#define CRAB_NUM_FRAMES 6
#define CRAB_FRAME_SPEED 8

typedef struct {
    Vector2 position;
    Rectangle hitbox;
    int currentFrame;
    int frameCounter;
    int frameSpeed;
} Crab;

Crab createCrab(Vector2 position, int frameSpeed);
void updateCrab(Crab* crab);
void drawCrab(Crab crab, Texture2D crabTexture);

#endif
