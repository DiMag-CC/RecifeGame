#include <raylib.h>
#include "stage1.h"
#include "player.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Deixa Eu");
    SetTargetFPS(60);

    Stage1 stage;
    initStage1(&stage);

    // Inicializar o jogador
    Player player = createPlayer((Vector2){ screenWidth / 2, GROUND_LEVEL }, 0, 3);

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        updateStage1(&stage, deltaTime);
        updatePlayer(&player, deltaTime);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        drawStage1(stage);
        drawPlayer(player);

        EndDrawing();
    }

    // Descarregar recursos
    unloadStage1(&stage);

    CloseWindow();

    return 0;
}