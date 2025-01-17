#include "raylib.h"
#include <stdio.h>
#include "game.h"

Game game;

int main(void)
{
    #if defined(PLATFORM_DESKTOP)
        //const int screenWidth = 450;
        //const int screenHeight = 800;
        const int screenWidth = 800;
        const int screenHeight = 300;
    #define GLSL_VERSION            330
    #else   // PLATFORM_ANDROID, PLATFORM_WEB
        const int screenWidth = 800;
        const int screenHeight = 400;
    #endif
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

