#include "stage1.h"
#include <stdio.h>
#include <stdlib.h>

void initStage1(Stage1 *stage) {

    initObstacleQueue(&stage->obstacleQueue);

    stage->obstacleSpawnTimer = 0.0f;

    stage->scrollSpeed = 100.0f;

    stage->background = LoadTexture("assets/img/background1.png");

    for (int i = 0; i < 5; i++) {
        char fileName[128];
        sprintf(fileName, "assets/img/building%d.png", i + 1);
        stage->buildings[i] = LoadTexture(fileName);
    }

    stage->roadPosition = 0.0f;
} 

void updateStage1(Stage1 *stage, Player *player, float deltaTime) {

    stage->obstacleSpawnTimer += deltaTime;
    stage->roadPosition +=  stage->scrollSpeed * deltaTime;
    ObstacleNode *current = stage->obstacleQueue.front;

    if (stage->obstacleSpawnTimer >= 2.0f) {
        Obstacle obstacle = createObstacle(
            (Vector2){ GetScreenWidth(), GROUND_LEVEL + 20 },
            OBSTACLE_CRAB
        );

        enqueueObstacle(&stage->obstacleQueue, obstacle);

        stage->obstacleSpawnTimer = 0.0f;
    }

    if (stage->roadPosition >= GetScreenWidth()) {
        stage->roadPosition = 0.0f;
    }

    while (current != NULL) {
        current->obstacle.position.x -= 300 * deltaTime;
        current->obstacle.data.crab.position.x = current->obstacle.position.x;
        current->obstacle.data.crab.hitbox.x = current->obstacle.position.x;
        current->obstacle.data.crab.hitbox.y = current->obstacle.position.y;

        current = current->next;
    }

    while (!isObstacleQueueEmpty(&stage->obstacleQueue) &&
       stage->obstacleQueue.front->obstacle.position.x < -50) {
    dequeueObstacle(&stage->obstacleQueue);
    }

    current = stage->obstacleQueue.front;
    while (current != NULL) {
        if (CheckCollisionRecs(player->hitbox, current->obstacle.data.crab.hitbox)) {
            player->lives -= 1;
            current->obstacle.position.x = -100.0f;
            current->obstacle.data.crab.position.x = -100.0f;
            current->obstacle.data.crab.hitbox.x = -100.0f;
        }
        current = current->next;
    }

}

void drawStage1(Stage1 *stage) {

    DrawTextureEx(stage->background, (Vector2){ 0, 0 }, 0.0f, 1.0f, WHITE);
    ObstacleNode *current = stage->obstacleQueue.front;

    for (int i = 0; i < 5; i++) {
        Vector2 position = { stage->roadPosition + i * 200, GetScreenHeight() - stage->buildings[i].height };
        DrawTextureEx(stage->buildings[i], position, 0.0f, 1.0f, WHITE);
    }

    while (current != NULL) {
        DrawRectangle(
            current->obstacle.position.x,
            current->obstacle.position.y,
            40,
            40,
            RED
        );

        current = current->next;
    }
}

void unloadStage1(Stage1* stage) {
    UnloadTexture(stage->background);
    for (int i = 0; i < 5; i++) {
        UnloadTexture(stage->buildings[i]);
    }
}
