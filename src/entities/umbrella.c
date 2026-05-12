#include "umbrella.h"

Umbrella createUmbrella(Vector2 position) {
    Umbrella umbrella;
    umbrella.position = position;
    umbrella.hitbox = (Rectangle){
        position.x,
        position.y,
        UMBRELLA_WIDTH,
        UMBRELLA_HEIGHT
    };
    umbrella.isCollected = 0;  // Não coletado
    umbrella.isActive = 1;     // Visível na tela
    
    return umbrella;
}

void drawUmbrella(Umbrella umbrella) {
    if (!umbrella.isActive) return;
    
    // Desenhar corpo do guarda-chuva (retângulo azul)
    DrawRectangleRec(umbrella.hitbox, BLUE);
    
    // Desenhar borda preta para destaque
    DrawRectangleLinesEx(umbrella.hitbox, 2, BLACK);
    
    // Desenhar bastão (linha preta)
    DrawLine(
        umbrella.position.x + UMBRELLA_WIDTH/2,
        umbrella.position.y + UMBRELLA_HEIGHT,
        umbrella.position.x + UMBRELLA_WIDTH/2,
        umbrella.position.y + UMBRELLA_HEIGHT + 15,
        BLACK
    );
}