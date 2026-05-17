#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "steps/stage3.h"
#include "entities/player.h"
#include "entities/pigeon.h"
#include "entities/raindrop.h"
#include "entities/umbrella.h"
#include "menu.h"
#include "structure/stepList.h"

// ========== CONSTANTES ==========
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define FPS 60

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Deixa Eu");
    SetTargetFPS(FPS);

    // ========== INICIALIZAR STAGE 3 ==========
    Stage3 stage3;

    // ========== INICIALIZAR PLAYER ==========
    Player player = createPlayer((Vector2){ SCREEN_WIDTH / 2, GROUND_LEVEL }, 150, 3);

    // ========== ESTADOS DO JOGO ==========
    int isGameOver = 0;
    float gameOverTimer = 0.0f;
    float totalGameTime = 0.0f;
    int slowedByRain = 0;      // Flag: player está lento por chuva/fezes?
    float slowDownTimer = 0.0f; // Timer de duração da lentidão

    // ========== MENU ==========
    Menu menu = createMenu();
    int inMenu = 1;

    // ========== FASES (Lista Circular) ==========
    Phase *phaseList = NULL;
    
    Phase *phase3 = createPhase(3, "Parque das Esculturas");
    
    insertPhase(&phaseList, phase3);
    
    Phase *currentPhase = phase3;
    printf("Fase atual: %s (numero %d)\n", currentPhase->phaseName, currentPhase->phaseNumber);
    fflush(stdout);

    // ========== LOOP PRINCIPAL ==========
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        // ===== ALTERAR TELA CHEIA =====
        if (IsKeyPressed(KEY_F)) {
            ToggleFullscreen();
        }

        // ===== MENU =====
        if (inMenu) {
            updateMenu(&menu);
            
            if (menu.screen == MENU_MAIN && IsKeyPressed(KEY_ENTER)) {
                if (menu.selectedOption == 0) {
                    // Iniciar jogo
                    inMenu = 0;
                    totalGameTime = 0.0f;
                    isGameOver = 0;
                    slowedByRain = 0;
                    slowDownTimer = 0.0f;
                    
                    initStage3(&stage3, &player);
                }
                else if (menu.selectedOption == 2) {
                    // Sair do jogo
                    break;
                }
            }
        }
        // ===== JOGO =====
        else {
            // ===== ATUALIZAR STAGE E PLAYER =====
            updateStage3(&stage3, &player, deltaTime);
            updatePlayer(&player, deltaTime);

            // ===== SISTEMA DE LENTIDÃO =====
            // Se o player estava lento, decrementar timer
            if (slowedByRain) {
                slowDownTimer -= deltaTime;
                
                if (slowDownTimer <= 0.0f) {
                    slowedByRain = 0;
                    slowDownTimer = 0.0f;
                    
                    // Restaurar velocidade normal
                    player.speed = 150.0f;  // Velocidade original
                }
            }

            // ===== VERIFICAR GAME OVER =====
            if (player.lives <= 0 && !isGameOver) {
                isGameOver = 1;
                gameOverTimer = 3.0f;
            }

            // ===== GAME OVER SCREEN =====
            if (isGameOver) {
                gameOverTimer -= deltaTime;
                
                if (IsKeyPressed(KEY_ENTER) || gameOverTimer <= 0) {
                    // Reset do jogo e voltar para o menu
                    player = createPlayer((Vector2){ SCREEN_WIDTH / 2, GROUND_LEVEL }, 150, 3);
                    unloadStage3(&stage3);
                    isGameOver = 0;
                    totalGameTime = 0.0f;
                    slowedByRain = 0;
                    slowDownTimer = 0.0f;
                    
                    menu = createMenu();
                    inMenu = 1;
                }
            }
            
            // ===== VICTORY REDIRECTION =====
            if (stage3.state == STAGE3_FINISHED) {
                if (IsKeyPressed(KEY_ENTER)) {
                    // Reset do jogo e voltar para o menu
                    player = createPlayer((Vector2){ SCREEN_WIDTH / 2, GROUND_LEVEL }, 150, 3);
                    unloadStage3(&stage3);
                    isGameOver = 0;
                    totalGameTime = 0.0f;
                    slowedByRain = 0;
                    slowDownTimer = 0.0f;
                    
                    menu = createMenu();
                    inMenu = 1;
                }
            }
            
            // ===== CONTAR TEMPO (se não está game over/venceu) =====
            if (!isGameOver && stage3.state != STAGE3_FINISHED) {
                totalGameTime += deltaTime;
            }
        }

        // ========== DESENHO ==========
        BeginDrawing();
        // Stage 3 usa fundo azul cel; evita flash branco chamando o clear correto
        ClearBackground(SKYBLUE);

        if (inMenu) {
            // ===== DESENHAR MENU =====
            drawMenu(menu);
        } 
        else {
            // ===== DESENHAR JOGO COM CÂMERA (ZOOM OUT PARA VER MAIS DA TELA) =====
            Camera2D camera = { 0 };
            camera.zoom = 0.8f; // Afasta a câmera para ver 25% mais do mapa
            camera.offset = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
            camera.target = (Vector2){ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
            
            BeginMode2D(camera);
            
            drawStage3(&stage3, &player);
            drawPlayer(player);
            
            EndMode2D();

            // ===== HUD - VIDAS =====
            char livesText[32];
            sprintf(livesText, "Vidas: %d", player.lives);
            DrawText(livesText, 10, 10, 20, BLACK);
            
            // ===== HUD - PONTOS =====
            char scoreText[64];
            sprintf(scoreText, "Pontos: %.0f", player.score);
            DrawText(scoreText, 10, 35, 20, BLACK);
            
            // ===== HUD - TEMPO =====
            char timeText[64];
            sprintf(timeText, "Tempo: %.1f seg", totalGameTime);
            DrawText(timeText, 10, 60, 20, BLACK);

            // ===== HUD - STATUS DE LENTIDÃO =====
            if (slowedByRain) {
                char slowText[64];
                sprintf(slowText, "LENTO! %.1f seg", slowDownTimer);
                DrawText(slowText, SCREEN_WIDTH - 200, 10, 16, RED);
                
                // Desenhar barra visual de lentidão
                DrawRectangle(SCREEN_WIDTH - 200, 30, 150, 10, RED);
                DrawRectangle(SCREEN_WIDTH - 200, 30, (int)(150 * (slowDownTimer / 2.0f)), 10, YELLOW);
            }

            // ===== HUD - PROTEÇÃO DO GUARDA-CHUVA =====
            if (player.hasUmbrella > 0) {
                char protectionText[64];
                sprintf(protectionText, "Protecao: %.1f s", player.umbrellaTimer);
                DrawText(protectionText, SCREEN_WIDTH - 250, 45, 16, GREEN);
            }

            // ===== DESENHAR GAME OVER =====
            if (isGameOver) {
                // Overlay escuro
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){0, 0, 0, 180});
                
                // Texto "GAME OVER"
                const char *gameOverText = "GAME OVER";
                int textWidth = MeasureText(gameOverText, 60);
                DrawText(gameOverText, (SCREEN_WIDTH - textWidth) / 2, 120, 60, RED);
                
                // Pontuação final
                char finalScoreText[128];
                sprintf(finalScoreText, "Pontos: %.0f | Tempo: %.1f seg", player.score, totalGameTime);
                textWidth = MeasureText(finalScoreText, 20);
                DrawText(finalScoreText, (SCREEN_WIDTH - textWidth) / 2, 200, 20, WHITE);
                
                // Instruções
                const char *restartText = "Pressione ENTER para voltar ao menu";
                textWidth = MeasureText(restartText, 16);
                DrawText(restartText, (SCREEN_WIDTH - textWidth) / 2, 250, 16, WHITE);
                
                // Timer de auto-reinício
                if (gameOverTimer > 0) {
                    char timerText[64];
                    sprintf(timerText, "Reiniciando em %.1f segundos", gameOverTimer);
                    textWidth = MeasureText(timerText, 14);
                    DrawText(timerText, (SCREEN_WIDTH - textWidth) / 2, 300, 14, YELLOW);
                }
            }
            
            // ===== DESENHAR VITORIA =====
            if (stage3.state == STAGE3_FINISHED) {
                // Overlay escuro com tom dourado sutil
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, (Color){10, 10, 30, 210});
                
                // Texto de Vitória ("Valeu a pena, mae.")
                const char *victoryText = "VALEU A PENA, MAE.";
                int textWidth = MeasureText(victoryText, 40);
                DrawText(victoryText, (SCREEN_WIDTH - textWidth) / 2, 120, 40, YELLOW);
                
                // Pontos e tempo
                char finalScoreText[128];
                sprintf(finalScoreText, "Pontos: %.0f | Tempo: %.1f seg", player.score, totalGameTime);
                textWidth = MeasureText(finalScoreText, 22);
                DrawText(finalScoreText, (SCREEN_WIDTH - textWidth) / 2, 190, 22, WHITE);
                
                // Instruções para retornar ao menu
                const char *returnText = "Pressione ENTER para voltar ao menu";
                textWidth = MeasureText(returnText, 18);
                DrawText(returnText, (SCREEN_WIDTH - textWidth) / 2, 250, 18, GREEN);
            }

            // ===== FPS (Debug) =====
            DrawFPS(SCREEN_WIDTH - 80, 10);
        }

        EndDrawing();
    }

    // ========== LIMPEZA ==========
    unloadStage3(&stage3);

    if (phaseList != NULL) {
        free(phase3);
    }

    CloseWindow();

    return 0;
}