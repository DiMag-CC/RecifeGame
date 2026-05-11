#include <raylib.h>
#include <stdio.h>
#include <string.h>
#include "steps/stage1.h"
#include "entities/player.h"
#include "menu.h"
#include "structure/stepList.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Deixa Eu");
    SetTargetFPS(60);

    Stage1 stage;
    initStage1(&stage);

    Player player = createPlayer((Vector2){ screenWidth / 2, GROUND_LEVEL }, 150, 3);

    int isGameOver = 0;
    float gameOverTimer = 0.0f;
    float totalGameTime = 0.0f; 

    Menu menu = createMenu();
    int inMenu = 1;

    Phase *phaseList = NULL;
    
    Phase *phase1 = createPhase(1, "Pedalando no Caos");
    Phase *phase2 = createPhase(2, "Boa Viagem");
    Phase *phase3 = createPhase(3, "Parque das Esculturas");
    
    insertPhase(&phaseList, phase1);
    insertPhase(&phaseList, phase2);
    insertPhase(&phaseList, phase3);
    
    Phase *currentPhase = phaseList;
    printf("Fase atual: %s (numero %d)\n", currentPhase->phaseName, currentPhase->phaseNumber);
    fflush(stdout); 

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        if (inMenu) {
            updateMenu(&menu);
            
            if (IsKeyPressed(KEY_ESCAPE) && menu.screen == MENU_CREDITS) {
                menu.screen = MENU_MAIN;
                menu.selectedOption = 0;
            }
            
            if (menu.screen == MENU_MAIN && IsKeyPressed(KEY_ENTER)) {
                if (menu.selectedOption == 0) {
                    // Iniciar jogo
                    inMenu = 0;
                }
                else if (menu.selectedOption == 2) {
                    // Sair do jogo
                    break;
                }
            }
        }
        else {
            updateStage1(&stage, &player, deltaTime);
            updatePlayer(&player, deltaTime);

            if (player.lives <= 0 && !isGameOver) {
                isGameOver = 1;
                gameOverTimer = 3.0f;
            }

            if (isGameOver) {
                gameOverTimer -= deltaTime;
                
                if (IsKeyPressed(KEY_ENTER) || gameOverTimer <= 0) {
                    // Reiniciar jogo
                    player = createPlayer((Vector2){ screenWidth / 2, GROUND_LEVEL }, 150, 3);
                    unloadStage1(&stage);
                    initStage1(&stage);
                    isGameOver = 0;
                    totalGameTime = 0.0f;
                    
                    menu = createMenu();
                    inMenu = 1;
                }
            }
            
            if (!isGameOver) {
                totalGameTime += deltaTime;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (inMenu) {
            drawMenu(menu);
        } 
        else {
            // Desenhar o jogo
            drawStage1(&stage);
            drawPlayer(player);
            DrawFPS(10, 10);
            
            // Desenhar vidas
            char livesText[32];
            sprintf(livesText, "Vidas: %d", player.lives);
            DrawText(livesText, 10, 10, 20, BLACK);
            
            // Desenhar tempo de jogo
            char timeText[64];
            sprintf(timeText, "Tempo: %.1f seg", totalGameTime);
            DrawText(timeText, 10, 40, 20, BLACK);
            
            if (isGameOver) {
                // Escurecer a tela
                DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0, 0, 0, 180});
                
                // Texto "GAME OVER"
                const char *gameOverText = "GAME OVER";
                int textWidth = MeasureText(gameOverText, 60);
                DrawText(gameOverText, (screenWidth - textWidth) / 2, 150, 60, RED);
                
                // Instruções
                const char *restartText = "Pressione ENTER para voltar ao menu";
                textWidth = MeasureText(restartText, 20);
                DrawText(restartText, (screenWidth - textWidth) / 2, 250, 20, WHITE);
                
                // Timer de auto-reinício
                if (gameOverTimer > 0) {
                    char timerText[64];
                    sprintf(timerText, "Reiniciando em %.1f segundos", gameOverTimer);
                    textWidth = MeasureText(timerText, 16);
                    DrawText(timerText, (screenWidth - textWidth) / 2, 320, 16, YELLOW);
                }
            }
        }

        EndDrawing();
    }
    // Desaloca Recursos
    unloadStage1(&stage);

    if (phaseList != NULL) {
        free(phase1);
        free(phase2);
        free(phase3);
    }

    CloseWindow();

    return 0;
}