#ifndef RAINDROP_H
#define RAINDROP_H

#include <raylib.h>

#define RAINDROP_WIDTH 3
#define RAINDROP_HEIGHT 10
#define RAINDROP_SPEED 300.0f

typedef struct {
    Vector2 position;
    Rectangle hitbox;
    float speed;
    int isActive;  // 1 = caindo, 0 = fora da tela
} Raindrop;

Raindrop createRaindrop(Vector2 position);
void updateRaindrop(Raindrop* raindrop, float deltaTime);
void drawRaindrop(Raindrop raindrop);

#endif