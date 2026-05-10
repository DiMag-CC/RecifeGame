#ifndef CRAB_H
#define CRAB_H

#include <raylib.h>

typedef struct {
    Vector2 position;
    Rectangle hitbox;
    int currentFrame;
    int frameCounter;
    int frameSpeed;
} Crab;


#endif