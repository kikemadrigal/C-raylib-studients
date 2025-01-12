#ifndef GAME_H
#define GAME_H


#include "player.h"
#include "raylib.h"


typedef enum state{
    INITIAL,
    MENU,
    GAME_LOOP,
    GAME_OVER,
    WIN
}Status;

typedef struct{
    Texture2D background;
    Status status;
    int ultima_pulsacion;
}Game;


void init_game(Game *game );
void update_game(Game *game);
void draw_game(Game *game);
void unload_game(Game *game);
#endif