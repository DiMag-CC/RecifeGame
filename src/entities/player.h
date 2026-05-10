#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

#define PLAYER_WIDTH 40
#define PLAYER_HEIGHT 60
#define PLAYER_JUMP_SPEED 420.0f
#define GRAVITY 980.0f
#define GROUND_LEVEL 380.0f
#define PLAYER_CROUCH_HEIGHT 35
#define PLAYER_STANDING_HEIGHT PLAYER_HEIGHT

typedef struct player {
    Vector2 position;
    Vector2 velocity;
    float speed;
    float score;
    int height;
    int lives;
} Player;

Player createPlayer(Vector2 initialPosition, float initialSpeed, int initialLives);
void updatePlayer(Player *player, float deltaTime);
void drawPlayer(Player player);

#endif
