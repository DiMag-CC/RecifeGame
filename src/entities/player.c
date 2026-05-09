#include <raylib.h>
#include "player.h"

Player createPlayer(Vector2 initialPosition, float initialSpeed,  int initialLives) {
    Player player;
    player.position = initialPosition;
    player.speed = initialSpeed;
    player.lives = initialLives;
    player.score = 0;

    return player;

}

void updatePlayer(Player *player, float deltaTime) {
    player->position.x += player->speed * deltaTime;

    if (IsKeyPressed(KEY_SPACE)) { // Pular
        player->velocity.y = -PLAYER_JUMP_SPEED;
    }

    player->velocity.y += GRAVITY * deltaTime;

    player->position.y += player->velocity.y * deltaTime;

    if (player->position.y >= GROUND_LEVEL) { // Está no chão?
        player->position.y = GROUND_LEVEL;
        player->velocity.y = 0;
    }

    if (IsKeyPressed(KEY_DOWN)) { // Abaixar
        player->height = PLAYER_CROUCH_HEIGHT;
    } else {
        player->height = PLAYER_STANDING_HEIGHT;
    }

    // Verificar colisões
}

void drawPlayer(Player player) {

    DrawRectangle(player.position.x, player.position.y, PLAYER_WIDTH, PLAYER_HEIGHT, WHITE);
    
}