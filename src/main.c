#include "raylib.h"
#include <stdio.h>
#include "game.h"

Game game;

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Students");
    SetTargetFPS(60);  
    init_game(&game);
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        update_game(&game);
        BeginDrawing();
            draw_game(&game);
        EndDrawing();

    }
    unload_game(&game);
    CloseWindow();              
    return 0;
}

