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
    int counter;
    Music music;
    //Sound fxWav;
    int level;
}Game;


void init_game(Game *game );
void update_game(Game *game);
void draw_game(Game *game);
void unload_game(Game *game);
void GUI(void);
void update_level_1(Game *game);
void check_collsisions(void);
#endif