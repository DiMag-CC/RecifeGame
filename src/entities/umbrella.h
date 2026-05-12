#ifndef UMBRELLA_H
#define UMBRELLA_H

#include <raylib.h>

#define UMBRELLA_WIDTH 50
#define UMBRELLA_HEIGHT 30

typedef struct {
    Vector2 position;
    Rectangle hitbox;
    int isCollected;  // 1 = coletado, 0 = esperando
    int isActive;     // 1 = visível na tela, 0 = desaparecido
} Umbrella;


// Cria um novo guarda-chuva na posição especificada
Umbrella createUmbrella(Vector2 position);

// Desenha o guarda-chuva na tela
void drawUmbrella(Umbrella umbrella);

#endif