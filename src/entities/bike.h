#ifndef BIKE_H
#define BIKE_H

#include <raylib.h>

typedef struct Bike {
    Vector2 position;
    Texture2D texture;
    Rectangle hitbox;
    float wheelAngle;
    float wheelSpeed;
} Bike;

#endif