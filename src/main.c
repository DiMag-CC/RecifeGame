#include <raylib.h>
#include "steps/stage1.h"
#include "entities/player.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Deixa Eu");
    SetTargetFPS(60);

    Stage1 stage;
    initStage1(&stage);

    // Inicializar o jogador
    Player player = createPlayer((Vector2){ screenWidth / 2, GROUND_LEVEL }, 150, 3);

    int isGameOver = 0;
    float gameOverTimer = 0.0f;
    float totalGameTime = 0.0f; 

    // Loop principal do jogo
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        updateStage1(&stage, &player, deltaTime);
        updatePlayer(&player, deltaTime);

        if (player.lives <= 0 && !isGameOver) {
            isGameOver = 1;
            gameOverTimer = 3.0f;  
        }

        if (isGameOver) {
            gameOverTimer -= deltaTime;
            
            if (IsKeyPressed(KEY_ENTER) || gameOverTimer <= 0) {
                player = createPlayer((Vector2){ screenWidth / 2, GROUND_LEVEL }, 150, 3);
                unloadStage1(&stage);
                initStage1(&stage);
                isGameOver = 0;
                totalGameTime = 0.0f;
                continue;
            }
        }
        
        if (!isGameOver) {
            totalGameTime += deltaTime;
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        drawStage1(&stage);
        drawPlayer(player);

        if (isGameOver) {
            DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0, 0, 0, 180});
            
            const char *gameOverText = "GAME OVER";
            int textWidth = MeasureText(gameOverText, 60);
            DrawText(gameOverText, (screenWidth - textWidth) / 2, 150, 60, RED);
            
            const char *restartText = "Pressione ENTER para reiniciar";
            textWidth = MeasureText(restartText, 20);
            DrawText(restartText, (screenWidth - textWidth) / 2, 250, 20, WHITE);
            
            if (gameOverTimer > 0) {
                char timerText[64];
                sprintf(timerText, "Reiniciando automaticamente em %.1f segundos", gameOverTimer);
                textWidth = MeasureText(timerText, 16);
                DrawText(timerText, (screenWidth - textWidth) / 2, 320, 16, YELLOW);
            }
            
            char livesText[32];
            sprintf(livesText, "Vidas: %d", (player.lives < 0) ? 0 : player.lives);
            DrawText(livesText, 20, 20, 20, RED);
        }

        DrawFPS(10, 10);
        EndDrawing();
    }

    // Descarregar recursos
    unloadStage1(&stage);

    CloseWindow();

    return 0;
}
