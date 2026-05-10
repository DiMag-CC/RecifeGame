#include "stage1.h"

void initStage1(Stage1 *stage) {

    stage->scrollSpeed = 100.0f;

    stage->background = LoadTexture("assets/img/background1.png");

    for (int i = 0; i < (sizeof(stage->buildings) / 4); i++) {
        char fileName[128];
        sprintf(fileName, "assets/img/building%d.png", i+1); 
        stage->buildings[i] = LoadTexture(fileName);
    }

    stage->roadPosition = 0.0f;
} 

void updateStage1(Stage1 *stage, float deltaTime) {

    stage->roadPosition +=  stage->scrollSpeed * deltaTime;

    if (stage->roadPosition >= GetScreenWidth()) {
        stage->roadPosition = 0.0f;
    }
}

void drawStage1(Stage1 *stage) {

    DrawTextureEx(stage.background, (Vector2){ 0, 0 }, 0.0f, 1.0f, WHITE);

    for (int i = 0; i < (sizeof(stage->buildings) / 4); i++) {
        Vector2 position = { stage.roadPosition + 1 * 200, GetScreenHeight() - stage.buildings[i].height };
        DrawTextureEx(stage.buildings[i], position, 0.0f, 1.0f, WHITE);
    }
}

void unloadStage1(Stage1* stage) {
    UnloadTexture(stage->background);
    for (int i = 0; i < 5; i++) {
        UnloadTexture(stage->buildings[i]);
    }
}