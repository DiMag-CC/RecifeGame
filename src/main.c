#include <stdio.h>
#include "structure/stepList.h"

#include "raylib.h"
#include "stage1.h"

int main() {
    // Inicialização da janela do jogo e outros recursos

    Stage1 stage;
    initStage1(&stage);

    while (!WindowShouldClose()) {


        updateStage1(&stage, GetFrameTime());



        BeginDrawing();
        ClearBackground(RAYWHITE);

        drawStage1(stage);

        EndDrawing();
    }

    // Descarregando recursos
    unloadStage1(&stage);

    CloseWindow();
    return 0;
}