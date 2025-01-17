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
    float end_time;
    //Sound fxWav;
    int level;
    bool is_paused;
}Game;


void init_game(Game *game );
void reset_game(Game *game);
void update_game(Game *game);
void draw_game(Game *game);
void unload_game(Game *game);
void GUI(Game *game);
void check_collsisions(void);

void init_level_1(Game *game);
void init_level_2(Game *game);
void update_level_1(Game *game);
#endif