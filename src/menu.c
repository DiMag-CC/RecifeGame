#include "menu.h"
#include <stdio.h>

Menu createMenu() {
    Menu menu;
    menu.screen = MENU_MAIN;
    menu.selectedOption = 0;
    return menu;
}

void updateMenu(Menu *menu) {
    if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
        menu->selectedOption--;
    }

    if (menu->selectedOption < 0) menu->selectedOption = 2;

    if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
        menu->selectedOption++;
    }

    if (menu->screen == MENU_CREDITS) {
        if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            menu->screen = MENU_MAIN;
        }
    }

    if (menu->selectedOption > 2) menu->selectedOption = 0;

    if (IsKeyPressed(KEY_ENTER)) {
        if (menu->selectedOption == 1) {
            menu->screen = MENU_CREDITS;
        }
    }

    if (IsKeyPressed(KEY_ESCAPE) && menu->screen == MENU_CREDITS) {
        menu->screen = MENU_MAIN;
        menu->selectedOption = 0;
    }
}

void drawMenu(Menu menu) {
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    
    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){20, 20, 60, 255});
    
    if (menu.screen == MENU_MAIN) {
        DrawText("DEIXA EU", 200, 50, 80, YELLOW);
        
        DrawText("Fuja de casa pela cidade do Recife!", 120, 150, 24, LIGHTGRAY);
        
        const char *options[] = { "Iniciar Jogo", "Creditos", "Sair" };
        int optionY[] = { 280, 360, 440 };
        
        for (int i = 0; i < 3; i++) {
            Color textColor = (menu.selectedOption == i) ? YELLOW : WHITE;
            
            if (menu.selectedOption == i) {
                DrawText(">", 200, optionY[i], 40, YELLOW);
            }
            
            DrawText(options[i], 260, optionY[i], 40, textColor);
        }
        
        DrawText("Use W/S ou Setas para navegar | ENTER para confirmar", 
                 50, screenHeight - 40, 16, GRAY);
    }
    else if (menu.screen == MENU_CREDITS) {
        DrawText("CREDITOS", 250, 50, 60, YELLOW);
        
        DrawText("Desenvolvido por:", 80, 150, 20, WHITE);
        DrawText("Arthur Moury", 120, 190, 18, LIGHTGRAY);
        DrawText("Diego Magnata", 120, 220, 18, LIGHTGRAY);
        DrawText("Luiza Barbosa", 120, 250, 18, LIGHTGRAY);
        DrawText("Helio de Moraes", 120, 280, 18, LIGHTGRAY);
        DrawText("Maria Augusta", 120, 310, 18, LIGHTGRAY);
        
        DrawText("Inspiracao: Super Mario + Subway Surfers", 100, 380, 18, LIGHTGRAY);
        DrawText("Deixa Eu", 150, 420, 18, LIGHTGRAY);
        
        DrawText("Pressione ESC para fechar", 180, screenHeight - 40, 16, GRAY);
    }
}


