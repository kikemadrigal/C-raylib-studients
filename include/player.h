#ifndef PLAYER_H
#define PLAYER_H
#include "raylib.h"
#include "input.h"
typedef struct {
    //Como las texturas se cargan cuando creamos la entidad en el game.c, no necesitamos cargarlas aquí
    Vector2 position;
    Vector2 init_position;
    short lives;
    long score;
    long hiscore;
    Texture2D texture;
    Rectangle rectangle_frame;
    int frame_counter;
    int frame_speed;
    //Sound hit;
}Player;

void initPlayer(Player *player);
void updatePlayer(Player *player, Input input);
void drawPlayer(Player *player, Input input);
void unloadPlayer(Player *player);
#endif