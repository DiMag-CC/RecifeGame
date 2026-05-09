#ifndef PLAYER_H
#define PLAYER_H

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct player {
    Vector2 position;
    Vector2 velocity;
    float speed;
    float score;
    int height;
    int lives;
} Player;

#endif