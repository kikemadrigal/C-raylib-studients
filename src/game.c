#include "raylib.h"
#include "game.h"
#include "input.h"
#include "player.h"
Player player;
Input input;

void init_game(Game *game ){
    game->status=INITIAL;
    game->ultima_pulsacion=-1;
    game->background=(Texture2D) LoadTexture("resources/background.png"); 
    initPlayer(&player);       
}

void update_game(Game *game){
    switch(game->status){
        case INITIAL:
            if (IsKeyPressed(KEY_ENTER)){
                game->status=GAME_LOOP;
            }
            break;
        case MENU:
            //Mostrar el menú
            break;
        case GAME_LOOP:
            //Jugar
            break;
        case GAME_OVER:
            //Mostrar la pantalla de game over
            break;
        case WIN:
            //Mostrar la pantalla de victoria
            break;
    }
}



void draw_game(Game *game){
    switch(game->status){
        case INITIAL:
            DrawText("¿Sobrevivirá la profesora\n\na los alumnos agobiantes?\n\n\n\n\nPress Enter to start", 50, 10, 20, WHITE);
            break;
        case MENU:
            //Mostrar el menú
            break;
        case GAME_LOOP:
            ClearBackground(RAYWHITE);
            input = readInput();
            updatePlayer(&player, input);
            DrawTextureEx(game->background, (Vector2){0,0}, 0.0f, 1.0f, WHITE);
            drawPlayer(&player, input);
            break;
        case GAME_OVER:
            //Mostrar la pantalla de game over
            break;
        case WIN:
            //Mostrar la pantalla de victoria
            break;
    }      
}

void unload_game(Game *game){
    //Libera la memoria del juego
    UnloadTexture(game->background);
    unloadPlayer(&player);
}

