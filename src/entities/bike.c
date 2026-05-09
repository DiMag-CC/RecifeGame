#include "bike.h"
#include <raylib.h>

Bike createBike(Vector2 initialPosition, const char* textureFileName, float initialWheelSpeed) {
    Bike bike;
    bike.position = initialPosition;
    bike.texture = LoadTexture(textureFileName);
    bike.wheelAngle = 0.0f;
    bike.wheelSpeed = initialWheelSpeed;
    return bike;
}

void updateBike(Bike* bike, Vector2 playerPosition, float deltaTime) {

    bike->position = playerPosition;

    // Atualiza o ângulo das rodas com base na velocidade
    bike->wheelAngle += bike->wheelSpeed * deltaTime;

    // Mantém o ângulo das rodas entre 0 e 360 graus
    if (bike->wheelAngle >= 360.0f) {
        bike->wheelAngle -= 360.0f;
    }
}

void drawBike(Bike bike) {
    // Desenha a textura da bicicleta na posição especificada
    DrawTextureEx(bike.texture, bike.position, 0.0f, 1.0f, WHITE);

    // Desenha as rodas da bicicleta com rotação
    Vector2 frontWheelCenter = {bike.position.x + 50, bike.position.y + 70};
    Vector2 backWheelCenter = {bike.position.x + 200, bike.position.y + 70};
    DrawCircleV(frontWheelCenter, 30, WHITE);
    DrawCircleV(backWheelCenter, 30, WHITE);
    DrawLineEx(frontWheelCenter, backWheelCenter, 10, WHITE);
    
    // Desenha os raios das rodas com base no ângulo atual
    for (int i = 0; i < 8; i++) {
        float angle = bike.wheelAngle + i * 45;
        Vector2 frontWheelRay = {frontWheelCenter.x + 25 * cosf(angle * DEG2RAD), frontWheelCenter.y + 25 * sinf(angle * DEG2RAD)};
        Vector2 backWheelRay = {backWheelCenter.x + 25 * cosf(angle * DEG2RAD), backWheelCenter.y + 25 * sinf(angle * DEG2RAD)};
        DrawLineEx(frontWheelCenter, frontWheelRay, 5, BLACK);
        DrawLineEx(backWheelCenter, backWheelRay, 5, BLACK);
    }
}