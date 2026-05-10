#include "shark.h"

Shark createShark(Vector2 position, Vector2 velocity) {
    Shark shark;
    shark.position = position;
    shark.hitbox = (Rectangle){position.x, position.y, SHARK_WIDTH, SHARK_HEIGHT};
    shark.velocity = velocity;
    return shark;
}

void updateShark(Shark* shark, Vector2 playerPosition, float deltaTime) {
    Vector2 direction = Vector2Subtract(playerPosition, shark->position);
    Vector2 normalizedDirection = Vector2Normalize(direction);
    shark->velocity = Vector2Scale(normalizedDirection, SHARK_SPEED);
    shark->position = Vector2Add(shark->position, Vector2Scale(shark->velocity, deltaTime));
    shark->hitbox.x = shark->position.x;
    shark->hitbox.y = shark->position.y;
}

void drawShark(Shark shark, Texture2D sharkTexture) {
    DrawTextureV(sharkTexture, shark.position, WHITE);
}