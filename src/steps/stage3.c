#include "stage3.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void initStage3(Stage3 *stage, Player *player) {
    stage->state = STAGE3_APPROACH;
    stage->scrollX = 0.0f;
    stage->scrollY = 0.0f;
    
    stage->towerTexture = LoadTexture("assets/img/torre_cristal.png");
    stage->cloudTexture = LoadTexture("assets/img/nuvem.png");
    stage->birdTexture = LoadTexture("assets/img/passaro.png");
    
    int towerHeight = stage->towerTexture.id > 0 ? stage->towerTexture.height : 600;
    int towerWidth = stage->towerTexture.id > 0 ? stage->towerTexture.width : 100;
    
    // Posiciona a torre mais para a direita para expandir o mapa (1200px)
    // Afunda a torre 20px no chão para cobrir qualquer transparência na base do sprite
    stage->towerPosition = (Vector2){ 1200.0f, (GROUND_LEVEL + PLAYER_HEIGHT + 20.0f) - towerHeight };
    
    stage->towerHitbox = (Rectangle){
        stage->towerPosition.x + (towerWidth * 0.2f), 
        stage->towerPosition.y,
        towerWidth * 0.6f, 
        towerHeight
    };
    
    // Staggered cloud positions, extremely high up, with randomized speed and scale
    stage->clouds[0].position = (Vector2){ rand() % 350, 10 + (rand() % 30) };
    stage->clouds[0].speed = 10.0f + (rand() % 25);
    stage->clouds[0].scale = 0.15f + (rand() % 10) / 100.0f; // Scale between 0.15 and 0.25
    
    stage->clouds[1].position = (Vector2){ 450 + (rand() % 300), 10 + (rand() % 30) };
    stage->clouds[1].speed = 10.0f + (rand() % 25);
    stage->clouds[1].scale = 0.15f + (rand() % 10) / 100.0f;
    
    // Inicializa 3 pássaros com distâncias e timers de cocô individuais
    stage->birds[0].position = (Vector2){ rand() % 250, 30 + (rand() % 30) };
    stage->birds[0].speed = 50.0f + (rand() % 30);
    stage->birds[0].poopTimer = 0.0f;
    stage->birds[0].poopInterval = 1.0f + (rand() % 200) / 100.0f;
    
    stage->birds[1].position = (Vector2){ 350 + (rand() % 300), 20 + (rand() % 30) };
    stage->birds[1].speed = 45.0f + (rand() % 40);
    stage->birds[1].poopTimer = 0.0f;
    stage->birds[1].poopInterval = 1.0f + (rand() % 200) / 100.0f;
    
    stage->birds[2].position = (Vector2){ 800 + (rand() % 400), 35 + (rand() % 25) };
    stage->birds[2].speed = 60.0f + (rand() % 30);
    stage->birds[2].poopTimer = 0.0f;
    stage->birds[2].poopInterval = 1.0f + (rand() % 200) / 100.0f;
    
    player->position = (Vector2){ 100, GROUND_LEVEL };
    player->isClimbing = false;
    player->velocity = (Vector2){0, 0};
    player->speed = 0.0f; // Para o auto-run
    player->movementControlledExternally = true; // Stage 3 controla o movimento
    
    for (int i = 0; i < MAX_BIRD_POOPS; i++) {
        stage->poops[i].active = false;
    }
}

void updateStage3(Stage3 *stage, Player *player, float deltaTime) {
    for (int i = 0; i < MAX_CLOUDS; i++) {
        stage->clouds[i].position.x -= stage->clouds[i].speed * deltaTime;
        if (stage->clouds[i].position.x < -200) {
            stage->clouds[i].position.x = 800 + (i * 400) + (rand() % 200); // Staggered reset
            stage->clouds[i].position.y = 10 + (rand() % 30);
            stage->clouds[i].speed = 10.0f + (rand() % 25);
            stage->clouds[i].scale = 0.15f + (rand() % 10) / 100.0f;
        }
    }
    
    for (int i = 0; i < MAX_BIRDS; i++) {
        stage->birds[i].position.x -= stage->birds[i].speed * deltaTime;
        if (stage->birds[i].position.x < -150) {
            // Reinicia mantendo-os distantes uns dos outros
            stage->birds[i].position.x = 800 + (i * 300) + (rand() % 200);
            stage->birds[i].position.y = 20 + (rand() % 35); 
            stage->birds[i].poopTimer = 0.0f;
            stage->birds[i].poopInterval = 1.0f + (rand() % 250) / 100.0f;
        }
    }

    if (stage->state == STAGE3_APPROACH) {
        float moveDelta = 200.0f * deltaTime;
        float maxScrollX = 650.0f; // Para o scroll quando a torre estiver a 550px na tela
        
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) {
            // Se o scroll já chegou ao máximo, permite andar livremente para a direita até o limite da tela/barreira
            if (stage->scrollX >= maxScrollX || player->position.x < 400.0f) {
                player->position.x += moveDelta;
            } else {
                // Rola a câmera (mantém jogador no centro e move o cenário)
                stage->scrollX += moveDelta;
                stage->towerPosition.x -= moveDelta;
                stage->towerHitbox.x -= moveDelta;
            }
        }
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) {
            // Se o jogador estiver à direita do centro (400) devido ao scroll ter parado, ele anda livremente para a esquerda primeiro
            if (player->position.x > 400.0f) {
                player->position.x -= moveDelta;
            } else if (player->position.x > 50.0f) {
                player->position.x -= moveDelta;
            } else if (stage->scrollX > 0) {
                stage->scrollX -= moveDelta;
                stage->towerPosition.x += moveDelta;
                stage->towerHitbox.x += moveDelta;
            }
        }
        
        // Barreira física após a torre: permite passar pela frente, andar no espaço extra, mas impede ir além do limite do mapa expandido
        int towerWidth = stage->towerTexture.id > 0 ? stage->towerTexture.width : 100;
        float barrierX = stage->towerPosition.x + towerWidth + 150.0f;
        if (player->position.x + PLAYER_WIDTH > barrierX) {
            player->position.x = barrierX - PLAYER_WIDTH;
        }
        
        // Verifica se o player está à frente da torre (sobreposto no eixo X)
        bool isOverlappingTowerX = (player->position.x + PLAYER_WIDTH >= stage->towerHitbox.x) && 
                                   (player->position.x <= stage->towerHitbox.x + stage->towerHitbox.width);
        
        // Se estiver sobreposto e pressionar W ou SETA PARA CIMA, inicia a escalada
        if (isOverlappingTowerX) {
            if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) {
                stage->state = STAGE3_CLIMBING;
                player->isClimbing = true;
                player->velocity.y = 0;
                player->position.x = stage->towerHitbox.x + stage->towerHitbox.width / 2.0f - PLAYER_WIDTH / 2.0f;
            }
        }
        
    } else if (stage->state == STAGE3_CLIMBING) {
        
        if (player->position.y < 200.0f) {
            float moveDelta = 200.0f - player->position.y;
            stage->scrollY -= moveDelta;
            player->position.y = 200.0f; 
            
            stage->towerPosition.y += moveDelta;
            stage->towerHitbox.y += moveDelta;
            
            for (int i = 0; i < MAX_CLOUDS; i++) stage->clouds[i].position.y += moveDelta;
            for (int i = 0; i < MAX_BIRDS; i++) stage->birds[i].position.y += moveDelta;
            for (int i = 0; i < MAX_BIRD_POOPS; i++) {
                if (stage->poops[i].active) {
                    stage->poops[i].position.y += moveDelta;
                }
            }
        }
        
        // Limita o jogador de ir abaixo da tela ao escalar
        if (player->position.y + player->height > 450.0f) {
            player->position.y = 450.0f - player->height;
        }
        
        if (player->position.x < stage->towerHitbox.x) player->position.x = stage->towerHitbox.x;
        if (player->position.x + PLAYER_WIDTH > stage->towerHitbox.x + stage->towerHitbox.width) player->position.x = stage->towerHitbox.x + stage->towerHitbox.width - PLAYER_WIDTH;
        
        if (stage->towerPosition.y > 450) { 
            stage->state = STAGE3_FINISHED;
            player->isClimbing = false; // finalizou subida
        }
    }
    
    // ===== GERENCIAMENTO DE COCO DOS PASSAROS =====
    for (int b = 0; b < MAX_BIRDS; b++) {
        stage->birds[b].poopTimer += deltaTime;
        if (stage->birds[b].poopTimer >= stage->birds[b].poopInterval) {
            stage->birds[b].poopTimer = 0.0f;
            // Randomiza o próximo intervalo individual do pássaro
            stage->birds[b].poopInterval = 1.0f + (rand() % 350) / 100.0f;
            
            // Spawna apenas se o pássaro estiver na tela
            if (stage->birds[b].position.x > 0.0f && stage->birds[b].position.x < 800.0f) {
                for (int i = 0; i < MAX_BIRD_POOPS; i++) {
                    if (!stage->poops[i].active) {
                        stage->poops[i].position = (Vector2){ stage->birds[b].position.x + 8.0f, stage->birds[b].position.y + 10.0f };
                        stage->poops[i].active = true;
                        stage->poops[i].speedY = 150.0f + (rand() % 150); // Velocidades de queda aleatórias (150 a 300)
                        break;
                    }
                }
            }
        }
    }
    
    // Atualiza poops
    for (int i = 0; i < MAX_BIRD_POOPS; i++) {
        if (stage->poops[i].active) {
            stage->poops[i].position.y += stage->poops[i].speedY * deltaTime;
            
            // Desativa ao sair da tela
            if (stage->poops[i].position.y > 450.0f) {
                stage->poops[i].active = false;
            }
            
            // Colisão com o hitbox do jogador (cocô é um pequeno círculo de raio 5)
            Rectangle poopHitbox = { stage->poops[i].position.x - 5, stage->poops[i].position.y - 5, 10, 10 };
            if (CheckCollisionRecs(player->hitbox, poopHitbox)) {
                player->lives = 0; // Se atingido pelas fezes, perde!
                stage->poops[i].active = false;
            }
        }
    }
}

void drawStage3(Stage3 *stage, Player *player) {
    (void)player;
    ClearBackground(SKYBLUE);
    
    // Chão: Recua para baixo conforme a torre desce (simulando a subida)
    int towerHeight = stage->towerTexture.id > 0 ? stage->towerTexture.height : 600;
    // Subtraímos 20.0f para que o chão verde cubra a base da torre, eliminando o gap visual
    float floorY = stage->towerPosition.y + towerHeight - 20.0f;
    
    // Expandido para preencher a tela inteira quando em modo zoom (começa antes e vai além das laterais)
    if (floorY < 560.0f) {
        DrawRectangle(-200, (int)floorY, 1200, 600 - (int)floorY, DARKGREEN);
    }
    
    for (int i = 0; i < MAX_CLOUDS; i++) {
        if (stage->cloudTexture.id > 0) {
            DrawTextureEx(stage->cloudTexture, stage->clouds[i].position, 0.0f, stage->clouds[i].scale, WHITE); // scale aleatório
        } else {
            DrawCircleV(stage->clouds[i].position, 15 * (stage->clouds[i].scale / 0.2f), WHITE);
        }
    }
    
    if (stage->towerTexture.id > 0) {
        DrawTextureEx(stage->towerTexture, stage->towerPosition, 0.0f, 1.0f, WHITE);
    } else {
        DrawRectangleRec(stage->towerHitbox, GRAY);
    }
    for (int i = 0; i < MAX_BIRDS; i++) {
        if (stage->birdTexture.id > 0) {
            DrawTextureEx(stage->birdTexture, stage->birds[i].position, 0.0f, 0.1f, WHITE); // scale super menor
        } else {
            DrawTriangle(
                (Vector2){stage->birds[i].position.x, stage->birds[i].position.y},
                (Vector2){stage->birds[i].position.x + 10, stage->birds[i].position.y - 5},
                (Vector2){stage->birds[i].position.x + 10, stage->birds[i].position.y + 5},
                BLACK
            );
        }
    }
    
    // Desenha cocôs dos pássaros (pequenos círculos marrons/cinzas)
    for (int i = 0; i < MAX_BIRD_POOPS; i++) {
        if (stage->poops[i].active) {
            DrawCircleV(stage->poops[i].position, 5.0f, (Color){ 127, 106, 79, 255 }); // Cor marrom de cocô
        }
    }
}

void unloadStage3(Stage3 *stage) {
    if (stage->towerTexture.id > 0) UnloadTexture(stage->towerTexture);
    if (stage->cloudTexture.id > 0) UnloadTexture(stage->cloudTexture);
    if (stage->birdTexture.id > 0) UnloadTexture(stage->birdTexture);
}
